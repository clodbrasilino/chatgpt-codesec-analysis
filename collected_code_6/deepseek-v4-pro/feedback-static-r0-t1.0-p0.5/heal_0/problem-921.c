#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **data;
    size_t count;
} Chunk;

typedef struct {
    Chunk *chunks;
    size_t chunk_count;
} ChunkedResult;

ChunkedResult chunk_tuples(const void *tuples, size_t tuple_size, size_t tuple_count, size_t chunk_size) {
    ChunkedResult result;
    result.chunks = NULL;
    result.chunk_count = 0;

    if (tuples == NULL || tuple_size == 0 || tuple_count == 0 || chunk_size == 0) {
        return result;
    }

    result.chunk_count = (tuple_count + chunk_size - 1) / chunk_size;
    result.chunks = (Chunk *)malloc(result.chunk_count * sizeof(Chunk));
    if (result.chunks == NULL) {
        result.chunk_count = 0;
        return result;
    }

    const unsigned char *tuple_ptr = (const unsigned char *)tuples;
    size_t remaining = tuple_count;
    size_t chunk_index = 0;

    while (remaining > 0) {
        size_t current_chunk_size = (remaining < chunk_size) ? remaining : chunk_size;
        result.chunks[chunk_index].data = (void **)malloc(current_chunk_size * sizeof(void *));
        if (result.chunks[chunk_index].data == NULL) {
            for (size_t i = 0; i < chunk_index; i++) {
                free(result.chunks[i].data);
            }
            free(result.chunks);
            result.chunks = NULL;
            result.chunk_count = 0;
            return result;
        }

        for (size_t i = 0; i < current_chunk_size; i++) {
            result.chunks[chunk_index].data[i] = (void *)tuple_ptr;
            tuple_ptr += tuple_size;
        }

        result.chunks[chunk_index].count = current_chunk_size;
        chunk_index++;
        remaining -= current_chunk_size;
    }

    return result;
}

void free_chunked_result(ChunkedResult *result) {
    if (result == NULL || result->chunks == NULL) {
        return;
    }

    for (size_t i = 0; i < result->chunk_count; i++) {
        free(result->chunks[i].data);
    }
    free(result->chunks);
    result->chunks = NULL;
    result->chunk_count = 0;
}

int main(void) {
    int tuples[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t tuple_size = sizeof(int);
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t chunk_size = 3;

    ChunkedResult result = chunk_tuples(tuples, tuple_size, tuple_count, chunk_size);

    if (result.chunks == NULL) {
        printf("Failed to chunk tuples\n");
        return 1;
    }

    printf("Number of chunks: %zu\n", result.chunk_count);
    for (size_t i = 0; i < result.chunk_count; i++) {
        printf("Chunk %zu: ", i);
        for (size_t j = 0; j < result.chunks[i].count; j++) {
            printf("%d ", *(int *)result.chunks[i].data[j]);
        }
        printf("\n");
    }

    free_chunked_result(&result);
    return 0;
}