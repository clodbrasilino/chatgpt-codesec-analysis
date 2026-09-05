#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} Chunk;

typedef struct {
    Chunk *chunks;
    size_t chunk_count;
} ChunkResult;

ChunkResult chunk_tuples(const Tuple *tuples, size_t tuple_count, size_t n) {
    ChunkResult result = {NULL, 0};

    if (tuples == NULL || n == 0) {
        return result;
    }

    if (tuple_count == 0) {
        result.chunks = (Chunk *)malloc(sizeof(Chunk));
        if (result.chunks == NULL) {
            return result;
        }
        result.chunk_count = 0;
        return result;
    }

    result.chunk_count = (tuple_count + n - 1) / n;
    result.chunks = (Chunk *)malloc(sizeof(Chunk) * result.chunk_count);
    if (result.chunks == NULL) {
        result.chunk_count = 0;
        return result;
    }

    for (size_t i = 0; i < result.chunk_count; i++) {
        size_t start = i * n;
        size_t current_chunk_size = n;
        if (start + n > tuple_count) {
            current_chunk_size = tuple_count - start;
        }

        result.chunks[i].items = (Tuple *)malloc(sizeof(Tuple) * current_chunk_size);
        if (result.chunks[i].items == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result.chunks[j].items);
            }
            free(result.chunks);
            result.chunks = NULL;
            result.chunk_count = 0;
            return result;
        }

        result.chunks[i].count = current_chunk_size;
        for (size_t k = 0; k < current_chunk_size; k++) {
            result.chunks[i].items[k] = tuples[start + k];
        }
    }

    return result;
}

void free_chunk_result(ChunkResult result) {
    for (size_t i = 0; i < result.chunk_count; i++) {
        free(result.chunks[i].items);
    }
    free(result.chunks);
}

int main(void) {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t n = 2;
    
    volatile const Tuple *volatile_tuples = tuples;
    volatile size_t volatile_tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    volatile size_t volatile_n = 2;

    ChunkResult result = chunk_tuples((const Tuple *)volatile_tuples, volatile_tuple_count, volatile_n);

    if (result.chunks == NULL) {
        if (volatile_tuple_count > 0 && volatile_n > 0) {
            return 1;
        }
    }

    for (size_t i = 0; i < result.chunk_count; i++) {
        for (size_t j = 0; j < result.chunks[i].count; j++) {
            printf("(%d, %d) ", result.chunks[i].items[j].a, result.chunks[i].items[j].b);
        }
        printf("\n");
    }

    free_chunk_result(result);

    return 0;
}