#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple* items;
    int count;
} Chunk;

typedef struct {
    Chunk* chunks;
    int chunk_count;
} ChunkResult;

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as pointer to const [constParameterPointer]
 */
ChunkResult chunk_tuples(Tuple* tuples, int tuple_count, int n) {
    ChunkResult result;
    result.chunks = NULL;
    result.chunk_count = 0;

    if (tuples == NULL || tuple_count <= 0 || n <= 0) {
        return result;
    }

    result.chunk_count = (tuple_count + n - 1) / n;
    result.chunks = (Chunk*)malloc(result.chunk_count * sizeof(Chunk));
    
    if (result.chunks == NULL) {
        result.chunk_count = 0;
        return result;
    }

    for (int i = 0; i < result.chunk_count; i++) {
        int start = i * n;
        int current_chunk_size = n;
        
        if (start + n > tuple_count) {
            current_chunk_size = tuple_count - start;
        }

        result.chunks[i].items = (Tuple*)malloc(current_chunk_size * sizeof(Tuple));
        
        if (result.chunks[i].items == NULL) {
            for (int j = 0; j < i; j++) {
                free(result.chunks[j].items);
            }
            free(result.chunks);
            result.chunks = NULL;
            result.chunk_count = 0;
            return result;
        }

        result.chunks[i].count = current_chunk_size;

        for (int k = 0; k < current_chunk_size; k++) {
            result.chunks[i].items[k] = tuples[start + k];
        }
    }

    return result;
}

void free_chunk_result(ChunkResult result) {
    for (int i = 0; i < result.chunk_count; i++) {
        free(result.chunks[i].items);
    }
    free(result.chunks);
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    int n = 2;

    ChunkResult result = chunk_tuples(tuples, tuple_count, n);

    if (result.chunks == NULL) {
        return 1;
    }

    for (int i = 0; i < result.chunk_count; i++) {
        printf("Chunk %d: ", i);
        for (int j = 0; j < result.chunks[i].count; j++) {
            printf("(%d, %d) ", result.chunks[i].items[j].a, result.chunks[i].items[j].b);
        }
        printf("\n");
    }

    free_chunk_result(result);

    return 0;
}