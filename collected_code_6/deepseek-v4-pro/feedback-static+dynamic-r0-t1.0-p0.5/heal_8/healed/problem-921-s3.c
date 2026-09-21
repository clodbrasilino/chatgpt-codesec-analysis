#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    void **data;
    size_t size;
} Chunk;

typedef struct {
    Chunk *chunks;
    size_t count;
} ChunkResult;

static void free_partial_chunks(Chunk *chunks, size_t count) {
    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < chunks[i].size; j++) {
            free(chunks[i].data[j]);
        }
        free(chunks[i].data);
    }
    free(chunks);
}

static void free_current_chunk_data(Chunk *chunk, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(chunk->data[i]);
    }
    free(chunk->data);
}

ChunkResult chunk_tuples(const void *tuples, size_t tuple_size, size_t tuple_count, size_t chunk_size) {
    ChunkResult result;
    result.chunks = NULL;
    result.count = 0;

    if (tuples == NULL || tuple_size == 0 || tuple_count == 0 || chunk_size == 0) {
        return result;
    }

    if (tuple_size > SIZE_MAX / tuple_count) {
        return result;
    }

    size_t total_size = tuple_count * tuple_size;
    if (total_size > SIZE_MAX - tuple_size) {
        return result;
    }

    if (chunk_size > tuple_count) {
        return result;
    }

    size_t full_chunks = tuple_count / chunk_size;
    size_t remainder = tuple_count % chunk_size;
    result.count = full_chunks + (remainder > 0 ? 1 : 0);

    if (result.count > SIZE_MAX / sizeof(Chunk)) {
        result.count = 0;
        return result;
    }

    result.chunks = (Chunk *)malloc(result.count * sizeof(Chunk));
    if (result.chunks == NULL) {
        result.count = 0;
        return result;
    }

    const unsigned char *src = (const unsigned char *)tuples;
    size_t chunk_index = 0;
    size_t src_offset = 0;

    for (size_t i = 0; i < full_chunks; i++) {
        result.chunks[chunk_index].size = chunk_size;

        if (chunk_size > SIZE_MAX / sizeof(void *)) {
            free_partial_chunks(result.chunks, chunk_index);
            result.chunks = NULL;
            result.count = 0;
            return result;
        }

        result.chunks[chunk_index].data = (void **)malloc(chunk_size * sizeof(void *));
        if (result.chunks[chunk_index].data == NULL) {
            free_partial_chunks(result.chunks, chunk_index);
            result.chunks = NULL;
            result.count = 0;
            return result;
        }

        size_t j;
        for (j = 0; j < chunk_size; j++) {
            result.chunks[chunk_index].data[j] = malloc(tuple_size);
            if (result.chunks[chunk_index].data[j] == NULL) {
                free_current_chunk_data(&result.chunks[chunk_index], j);
                free_partial_chunks(result.chunks, chunk_index);
                result.chunks = NULL;
                result.count = 0;
                return result;
            }

            if (src_offset + tuple_size > total_size) {
                free_current_chunk_data(&result.chunks[chunk_index], j + 1);
                free_partial_chunks(result.chunks, chunk_index);
                result.chunks = NULL;
                result.count = 0;
                return result;
            }

            if (tuple_size > 0) {
                memcpy(result.chunks[chunk_index].data[j], src + src_offset, tuple_size);
            }
            src_offset += tuple_size;
        }
        chunk_index++;
    }

    if (remainder > 0) {
        result.chunks[chunk_index].size = remainder;

        if (remainder > SIZE_MAX / sizeof(void *)) {
            free_partial_chunks(result.chunks, chunk_index);
            result.chunks = NULL;
            result.count = 0;
            return result;
        }

        result.chunks[chunk_index].data = (void **)malloc(remainder * sizeof(void *));
        if (result.chunks[chunk_index].data == NULL) {
            free_partial_chunks(result.chunks, chunk_index);
            result.chunks = NULL;
            result.count = 0;
            return result;
        }

        size_t j;
        for (j = 0; j < remainder; j++) {
            result.chunks[chunk_index].data[j] = malloc(tuple_size);
            if (result.chunks[chunk_index].data[j] == NULL) {
                free_current_chunk_data(&result.chunks[chunk_index], j);
                free_partial_chunks(result.chunks, chunk_index);
                result.chunks = NULL;
                result.count = 0;
                return result;
            }

            if (src_offset + tuple_size > total_size) {
                free_current_chunk_data(&result.chunks[chunk_index], j + 1);
                free_partial_chunks(result.chunks, chunk_index);
                result.chunks = NULL;
                result.count = 0;
                return result;
            }

            if (tuple_size > 0) {
                memcpy(result.chunks[chunk_index].data[j], src + src_offset, tuple_size);
            }
            src_offset += tuple_size;
        }
    }

    return result;
}

void free_chunk_result(ChunkResult *result) {
    if (result == NULL || result->chunks == NULL) {
        return;
    }

    for (size_t i = 0; i < result->count; i++) {
        for (size_t j = 0; j < result->chunks[i].size; j++) {
            free(result->chunks[i].data[j]);
        }
        free(result->chunks[i].data);
    }
    free(result->chunks);
    result->chunks = NULL;
    result->count = 0;
}

int main(void) {
    int tuples[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t tuple_size = sizeof(int);
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t chunk_size = 3;

    ChunkResult result = chunk_tuples(tuples, tuple_size, tuple_count, chunk_size);

    if (result.chunks == NULL) {
        fprintf(stderr, "Failed to chunk tuples\n");
        return 1;
    }

    for (size_t i = 0; i < result.count; i++) {
        printf("Chunk %zu: ", i);
        for (size_t j = 0; j < result.chunks[i].size; j++) {
            printf("%d ", *(int *)result.chunks[i].data[j]);
        }
        printf("\n");
    }

    free_chunk_result(&result);
    return 0;
}