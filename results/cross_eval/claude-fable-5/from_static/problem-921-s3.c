#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *elements;
    size_t count;
} Chunk;

typedef struct {
    Chunk *chunks;
    size_t chunk_count;
} ChunkResult;

static void free_chunk_result(ChunkResult *result)
{
    if (result == NULL) {
        return;
    }

    if (result->chunks != NULL) {
        for (size_t i = 0; i < result->chunk_count; i++) {
            free(result->chunks[i].elements);
            result->chunks[i].elements = NULL;
        }
        free(result->chunks);
        result->chunks = NULL;
    }

    result->chunk_count = 0;
    free(result);
}

static ChunkResult *chunk_tuples(const int *data, size_t data_len, size_t n)
{
    ChunkResult *result;
    size_t num_chunks;

    if (data == NULL || data_len == 0 || n == 0) {
        return NULL;
    }

    num_chunks = (data_len + n - 1) / n;

    result = malloc(sizeof(ChunkResult));
    if (result == NULL) {
        return NULL;
    }

    result->chunks = calloc(num_chunks, sizeof(Chunk));
    if (result->chunks == NULL) {
        free(result);
        return NULL;
    }
    result->chunk_count = num_chunks;

    for (size_t i = 0; i < num_chunks; i++) {
        const size_t offset = i * n;
        const size_t remaining = data_len - offset;
        result->chunks[i].count = (remaining < n) ? remaining : n;

        result->chunks[i].elements = malloc(result->chunks[i].count * sizeof(int));
        if (result->chunks[i].elements == NULL) {
            free_chunk_result(result);
            return NULL;
        }

        for (size_t j = 0; j < result->chunks[i].count; j++) {
            result->chunks[i].elements[j] = data[offset + j];
        }
    }

    return result;
}

static void print_chunks(const ChunkResult *result)
{
    if (result == NULL) {
        return;
    }

    for (size_t i = 0; i < result->chunk_count; i++) {
        printf("Chunk %zu: (", i);
        for (size_t j = 0; j < result->chunks[i].count; j++) {
            printf("%d", result->chunks[i].elements[j]);
            if (j + 1 < result->chunks[i].count) {
                printf(", ");
            }
        }
        printf(")\n");
    }
}

int main(void)
{
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t n = 3;
    ChunkResult *result;

    result = chunk_tuples(data, data_len, n);
    if (result == NULL) {
        fprintf(stderr, "Failed to chunk tuples\n");
        return EXIT_FAILURE;
    }

    print_chunks(result);
    free_chunk_result(result);

    return EXIT_SUCCESS;
}