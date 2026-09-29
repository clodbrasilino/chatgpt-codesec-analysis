#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **data;
    size_t size;
} Chunk;

typedef struct {
    Chunk *chunks;
    size_t num_chunks;
    size_t chunk_size;
} ChunkedTuples;

ChunkedTuples *chunk_tuples(const void *tuples, size_t tuple_size, size_t num_tuples, size_t chunk_size) {
    if (tuples == NULL || tuple_size == 0 || num_tuples == 0 || chunk_size == 0) {
        return NULL;
    }

    ChunkedTuples *result = (ChunkedTuples *)malloc(sizeof(ChunkedTuples));
    if (result == NULL) {
        return NULL;
    }

    result->chunk_size = chunk_size;
    result->num_chunks = (num_tuples + chunk_size - 1) / chunk_size;
    result->chunks = (Chunk *)calloc(result->num_chunks, sizeof(Chunk));
    if (result->chunks == NULL) {
        free(result);
        return NULL;
    }

    const unsigned char *tuple_ptr = (const unsigned char *)tuples;
    size_t remaining = num_tuples;

    for (size_t i = 0; i < result->num_chunks; i++) {
        size_t current_chunk_size = (remaining < chunk_size) ? remaining : chunk_size;
        result->chunks[i].size = current_chunk_size;
        result->chunks[i].data = (void **)malloc(current_chunk_size * sizeof(void *));
        if (result->chunks[i].data == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result->chunks[j].data);
            }
            free(result->chunks);
            free(result);
            return NULL;
        }

        for (size_t j = 0; j < current_chunk_size; j++) {
            result->chunks[i].data[j] = (void *)tuple_ptr;
            tuple_ptr += tuple_size;
        }
        remaining -= current_chunk_size;
    }

    return result;
}

void free_chunked_tuples(ChunkedTuples *chunked) {
    if (chunked == NULL) {
        return;
    }

    if (chunked->chunks != NULL) {
        for (size_t i = 0; i < chunked->num_chunks; i++) {
            free(chunked->chunks[i].data);
        }
        free(chunked->chunks);
    }
    free(chunked);
}

int main(void) {
    int tuples[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t tuple_size = sizeof(int);
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t chunk_size = 3;

    ChunkedTuples *chunked = chunk_tuples(tuples, tuple_size, num_tuples, chunk_size);
    if (chunked == NULL) {
        fprintf(stderr, "Failed to chunk tuples\n");
        return 1;
    }

    printf("Number of chunks: %zu\n", chunked->num_chunks);
    for (size_t i = 0; i < chunked->num_chunks; i++) {
        printf("Chunk %zu (size %zu): ", i, chunked->chunks[i].size);
        for (size_t j = 0; j < chunked->chunks[i].size; j++) {
            printf("%d ", *(int *)chunked->chunks[i].data[j]);
        }
        printf("\n");
    }

    free_chunked_tuples(chunked);
    return 0;
}