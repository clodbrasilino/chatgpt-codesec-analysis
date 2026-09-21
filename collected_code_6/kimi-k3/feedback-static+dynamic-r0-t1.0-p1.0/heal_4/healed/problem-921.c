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
    if (a == 0 || b == 0) {
        *result = 0;
        return 0;
    }
    if (a > SIZE_MAX / b) {
        return -1;
    }
    *result = a * b;
    return 0;
}

static int safe_add_size(size_t a, size_t b, size_t *result) {
    if (a > SIZE_MAX - b) {
        return -1;
    }
    *result = a + b;
    return 0;
}

static void cleanup_partial_chunks(ChunkResult *result, size_t count) {
    size_t k;
    for (k = 0; k < count; k++) {
        free(result->chunks[k].data);
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
    size_t total_bytes;
    
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
    
    if (safe_multiply_size(total_elements, sizeof(int), &total_bytes) != 0) {
        return -1;
    }
    
    num_chunks = (total_tuples + chunk_size - 1) / chunk_size;
    
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
        size_t copy_elements;
        size_t copy_bytes;
        size_t offset_elements;
        size_t offset_bytes;
        size_t end_elements;
        
        if (safe_multiply_size(current_chunk_size, tuple_size, &copy_elements) != 0) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        if (safe_multiply_size(copy_elements, sizeof(int), &copy_bytes) != 0) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        if (safe_multiply_size(i, chunk_size, &offset_elements) != 0 ||
            safe_multiply_size(offset_elements, tuple_size, &offset_elements) != 0) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        if (safe_multiply_size(offset_elements, sizeof(int), &offset_bytes) != 0) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        if (safe_add_size(offset_elements, copy_elements, &end_elements) != 0 ||
            end_elements > total_elements) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        if (offset_bytes > total_bytes || copy_bytes > total_bytes - offset_bytes) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        result->chunks[i].data = (int *)malloc(copy_bytes);
        if (result->chunks[i].data == NULL) {
            cleanup_partial_chunks(result, i);
            return -1;
        }
        
        result->chunks[i].tuple_size = tuple_size;
        result->chunks[i].num_tuples = current_chunk_size;
        
        if (copy_bytes > 0 && copy_bytes <= (size_t)(total_bytes - offset_bytes)) {
            memcpy(result->chunks[i].data, 
                   (const char *)source + offset_bytes,
                   copy_bytes);
        } else {
            cleanup_partial_chunks(result, i + 1);
            return -1;
        }
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