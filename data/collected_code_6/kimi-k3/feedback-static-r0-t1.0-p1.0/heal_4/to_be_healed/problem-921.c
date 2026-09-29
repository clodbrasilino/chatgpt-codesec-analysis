#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

typedef struct {
    int *data;
    size_t tuple_size;
    size_t num_tuples;
} TupleSet;

typedef struct {
    TupleSet *chunks;
    size_t num_chunks;
} ChunkResult;

static int safe_multiply_size(size_t a, size_t b, size_t *result) {
    if (a != 0 && b > SIZE_MAX / a) {
        return -1;
    }
    *result = a * b;
    return 0;
}

static int safe_add_size(size_t a, size_t b, size_t *result) {
    if (b > SIZE_MAX - a) {
        return -1;
    }
    *result = a + b;
    return 0;
}

static void cleanup_partial_chunks(ChunkResult *result, size_t count) {
    size_t k;
    for (k = 0; k < count; k++) {
        free(result->chunks[k].data);
        result->chunks[k].data = NULL;
    }
    free(result->chunks);
    result->chunks = NULL;
    result->num_chunks = 0;
}

int chunk_tuples(const int *source, size_t total_tuples, size_t tuple_size, 
                 size_t chunk_size, ChunkResult *result) {
    size_t i;
    size_t num_chunks;
    size_t total_elements;
    size_t chunk_elements;
    
    if (source == NULL || result == NULL || tuple_size == 0 || chunk_size == 0) {
        return -1;
    }
    
    if (total_tuples == 0) {
        result->chunks = NULL;
        result->num_chunks = 0;
        return 0;
    }
    
    if (safe_multiply_size(total_tuples, tuple_size, &total_elements) != 0) {
        return -1;
    }
    
    if (safe_multiply_size(chunk_size, tuple_size, &chunk_elements) != 0) {
        return -1;
    }
    
    if (safe_add_size(total_tuples, chunk_size - 1, &num_chunks) != 0) {
        return -1;
    }
    num_chunks = num_chunks / chunk_size;
    
    if (num_chunks > SIZE_MAX / sizeof(TupleSet)) {
        return -1;
    }
    
    result->chunks = (TupleSet *)calloc(num_chunks, sizeof(TupleSet));
    if (result->chunks == NULL) {
        return -1;
    }
    result->num_chunks = num_chunks;
    
    for (i = 0; i < num_chunks; i++) {
        size_t current_chunk_size = (i == num_chunks - 1) ? 
                            (total_tuples - i * chunk_size) : chunk_size;
        size_t current_elements;
        size_t copy_size;
        size_t source_offset;
        size_t remaining_elements;
        
        if (safe_multiply_size(current_chunk_size, tuple_size, &current_elements) != 0) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        if (safe_multiply_size(current_elements, sizeof(int), &copy_size) != 0) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        if (copy_size == 0) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        if (safe_multiply_size(i, chunk_elements, &source_offset) != 0) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        if (source_offset > total_elements) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        remaining_elements = total_elements - source_offset;
        
        if (current_elements > remaining_elements) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        result->chunks[i].data = (int *)malloc(copy_size);
        if (result->chunks[i].data == NULL) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        result->chunks[i].tuple_size = tuple_size;
        result->chunks[i].num_tuples = current_chunk_size;
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result->chunks[i].data, 
               source + source_offset,
               copy_size);
    }
    
    return 0;
}

void free_chunk_result(ChunkResult *result) {
    if (result == NULL) {
        return;
    }
    
    if (result->chunks != NULL) {
        size_t i;
        for (i = 0; i < result->num_chunks; i++) {
            free(result->chunks[i].data);
            result->chunks[i].data = NULL;
        }
        free(result->chunks);
        result->chunks = NULL;
    }
    result->num_chunks = 0;
}

int main(void) {
    const int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    size_t tuple_size = 3;
    size_t total_tuples = 5;
    size_t chunk_size = 2;
    ChunkResult result;
    size_t i;
    size_t j;
    size_t k;
    
    if (chunk_tuples(data, total_tuples, tuple_size, chunk_size, &result) != 0) {
        fprintf(stderr, "Error: Failed to chunk tuples\n");
        return EXIT_FAILURE;
    }
    
    printf("Original tuples (size %zu):\n", tuple_size);
    for (i = 0; i < total_tuples; i++) {
        printf("(");
        for (j = 0; j < tuple_size; j++) {
            printf("%d", data[i * tuple_size + j]);
            if (j < tuple_size - 1) {
                printf(", ");
            }
        }
        printf(")");
        if (i < total_tuples - 1) {
            printf(" ");
        }
    }
    printf("\n\n");
    
    printf("Chunked into %zu chunks (chunk size %zu):\n", result.num_chunks, chunk_size);
    for (i = 0; i < result.num_chunks; i++) {
        printf("Chunk %zu: ", i);
        for (j = 0; j < result.chunks[i].num_tuples; j++) {
            printf("(");
            for (k = 0; k < result.chunks[i].tuple_size; k++) {
                printf("%d", result.chunks[i].data[j * result.chunks[i].tuple_size + k]);
                if (k < result.chunks[i].tuple_size - 1) {
                    printf(", ");
                }
            }
            printf(")");
            if (j < result.chunks[i].num_tuples - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    
    free_chunk_result(&result);
    
    return EXIT_SUCCESS;
}