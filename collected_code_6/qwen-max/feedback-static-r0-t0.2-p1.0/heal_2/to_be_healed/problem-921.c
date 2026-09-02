#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} TupleChunk;

TupleChunk* create_chunk(size_t n, size_t chunk_size) {
    TupleChunk *chunk = (TupleChunk *)malloc(sizeof(TupleChunk));
    if (chunk == NULL) {
        return NULL;
    }
    chunk->data = (int *)malloc(n * chunk_size * sizeof(int));
    if (chunk->data == NULL) {
        free(chunk);
        return NULL;
    }
    chunk->length = chunk_size;
    return chunk;
}

void free_chunk(TupleChunk *chunk) {
    if (chunk != NULL) {
        free(chunk->data);
        free(chunk);
    }
}

TupleChunk* chunk_tuples(const int *tuples, size_t total_tuples, size_t n, size_t chunk_size) {
    TupleChunk *chunk = create_chunk(n, chunk_size);
    if (chunk == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < chunk_size; ++i) {
        for (size_t j = 0; j < n; ++j) {
            chunk->data[i * n + j] = tuples[i * n + j];
        }
    }
    return chunk;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'tuples' can be declared as const array [constVariable]
     */
    int tuples[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    size_t total_tuples = 4;
    size_t n = 3;
    size_t chunk_size = 2;

    TupleChunk *chunk = chunk_tuples(tuples, total_tuples, n, chunk_size);
    if (chunk != NULL) {
        for (size_t i = 0; i < chunk->length; ++i) {
            for (size_t j = 0; j < n; ++j) {
                printf("%d ", chunk->data[i * n + j]);
            }
            printf("\n");
        }
        free_chunk(chunk);
    } else {
        printf("Failed to create chunk\n");
    }

    return 0;
}