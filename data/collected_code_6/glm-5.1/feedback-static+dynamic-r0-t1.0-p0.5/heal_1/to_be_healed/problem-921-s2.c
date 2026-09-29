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
    size_t count;
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
        result.count = 0;
        return result;
    }

    size_t num_chunks = (tuple_count + n - 1) / n;
    result.chunks = (Chunk *)malloc(num_chunks * sizeof(Chunk));
    if (result.chunks == NULL) {
        return result;
    }
    result.count = num_chunks;

    for (size_t i = 0; i < num_chunks; i++) {
        size_t start = i * n;
        size_t remaining = tuple_count - start;
        size_t current_chunk_size = remaining < n ? remaining : n;

        result.chunks[i].items = (Tuple *)malloc(current_chunk_size * sizeof(Tuple));
        if (result.chunks[i].items == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result.chunks[j].items);
            }
            free(result.chunks);
            result.chunks = NULL;
            result.count = 0;
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
    for (size_t i = 0; i < result.count; i++) {
        free(result.chunks[i].items);
    }
    free(result.chunks);
}

int main(void) {
    Tuple data[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    /* Possible weaknesses found:
     *  Assignment 'data_count=sizeof(data)/sizeof(data[0])', assigned value is 5
     */
    size_t data_count = sizeof(data) / sizeof(data[0]);
    size_t n = 2;

    ChunkResult res = chunk_tuples(data, data_count, n);

    /* Possible weaknesses found:
     *  Condition 'data_count>0' is always true [knownConditionTrueFalse]
     *  Condition 'data_count>0' is always true
     */
    if (res.chunks == NULL && data_count > 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < res.count; i++) {
        printf("Chunk %zu: ", i);
        for (size_t j = 0; j < res.chunks[i].count; j++) {
            printf("(%d, %d) ", res.chunks[i].items[j].a, res.chunks[i].items[j].b);
        }
        printf("\n");
    }

    free_chunk_result(res);

    return EXIT_SUCCESS;
}