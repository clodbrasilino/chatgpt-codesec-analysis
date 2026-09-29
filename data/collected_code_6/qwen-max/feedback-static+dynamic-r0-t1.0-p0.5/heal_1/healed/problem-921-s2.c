#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
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
    chunk->size = chunk_size;
    return chunk;
}

void free_chunk(TupleChunk *chunk) {
    if (chunk != NULL) {
        free(chunk->data);
        free(chunk);
    }
}

void fill_chunk(TupleChunk *chunk, const int *source, size_t n, size_t start_index) {
    for (size_t i = 0; i < chunk->size; ++i) {
        for (size_t j = 0; j < n; ++j) {
            chunk->data[i * n + j] = source[start_index + i * n + j];
        }
    }
}

void print_chunk(const TupleChunk *chunk, size_t n) {
    for (size_t i = 0; i < chunk->size; ++i) {
        for (size_t j = 0; j < n; ++j) {
            printf("%d ", chunk->data[i * n + j]);
        }
        printf("\n");
    }
}

int main() {
    size_t n = 3;
    size_t total_tuples = 9;
    size_t chunk_size = 3;

    const int data[total_tuples * n] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

    TupleChunk *chunk = create_chunk(n, chunk_size);
    if (chunk == NULL) {
        return 1;
    }

    fill_chunk(chunk, data, n, 0);
    print_chunk(chunk, n);

    free_chunk(chunk);
    return 0;
}