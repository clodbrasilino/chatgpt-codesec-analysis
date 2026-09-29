#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple** chunks;
    size_t* chunk_sizes;
    size_t num_chunks;
} ChunkResult;

ChunkResult chunk_tuples(const Tuple* tuples, size_t num_tuples, size_t n) {
    ChunkResult result = {NULL, NULL, 0};
    
    if (tuples == NULL || n == 0) {
        return result;
    }
    
    if (num_tuples == 0) {
        return result;
    }

    if (num_tuples > SIZE_MAX - n + 1) {
        return result;
    }

    size_t num_chunks = (num_tuples + n - 1) / n;
    
    if (num_chunks > SIZE_MAX / sizeof(Tuple*) || num_chunks > SIZE_MAX / sizeof(size_t)) {
        return result;
    }

    result.chunks = (Tuple**)malloc(num_chunks * sizeof(Tuple*));
    result.chunk_sizes = (size_t*)malloc(num_chunks * sizeof(size_t));

    if (result.chunks == NULL || result.chunk_sizes == NULL) {
        free(result.chunks);
        free(result.chunk_sizes);
        result.chunks = NULL;
        result.chunk_sizes = NULL;
        return result;
    }

    result.num_chunks = num_chunks;

    for (size_t i = 0; i < num_chunks; i++) {
        size_t start = i * n;
        size_t current_size = n;
        if (start + current_size > num_tuples) {
            current_size = num_tuples - start;
        }

        if (current_size > SIZE_MAX / sizeof(Tuple)) {
            for (size_t j = 0; j < i; j++) {
                free(result.chunks[j]);
            }
            free(result.chunks);
            free(result.chunk_sizes);
            result.chunks = NULL;
            result.chunk_sizes = NULL;
            result.num_chunks = 0;
            return result;
        }

        result.chunks[i] = (Tuple*)malloc(current_size * sizeof(Tuple));
        if (result.chunks[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result.chunks[j]);
            }
            free(result.chunks);
            free(result.chunk_sizes);
            result.chunks = NULL;
            result.chunk_sizes = NULL;
            result.num_chunks = 0;
            return result;
        }

        for (size_t k = 0; k < current_size; k++) {
            result.chunks[i][k] = tuples[start + k];
        }
        result.chunk_sizes[i] = current_size;
    }

    return result;
}

void free_chunk_result(ChunkResult result) {
    for (size_t i = 0; i < result.num_chunks; i++) {
        free(result.chunks[i]);
    }
    free(result.chunks);
    free(result.chunk_sizes);
}

int main(void) {
    Tuple data[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    size_t num_tuples = sizeof(data) / sizeof(data[0]);
    size_t n = 2;

    ChunkResult res = chunk_tuples(data, num_tuples, n);
    
    if (res.chunks != NULL) {
        for (size_t i = 0; i < res.num_chunks; i++) {
            for (size_t j = 0; j < res.chunk_sizes[i]; j++) {
                printf("(%d, %d) ", res.chunks[i][j].a, res.chunks[i][j].b);
            }
            printf("\n");
        }
        free_chunk_result(res);
    }

    return 0;
}