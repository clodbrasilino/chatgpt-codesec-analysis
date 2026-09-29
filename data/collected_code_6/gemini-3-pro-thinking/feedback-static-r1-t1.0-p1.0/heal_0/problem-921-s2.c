#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int *data;
    size_t num_tuples;
    size_t tuple_size;
} Chunk;

typedef struct {
    Chunk *chunks;
    size_t num_chunks;
} ChunkedData;

void free_chunked_data(ChunkedData *chunked_data) {
    if (!chunked_data) {
        return;
    }
    if (chunked_data->chunks) {
        for (size_t i = 0; i < chunked_data->num_chunks; ++i) {
            free(chunked_data->chunks[i].data);
        }
        free(chunked_data->chunks);
    }
    free(chunked_data);
}

ChunkedData* chunk_tuples(const int *input_data, size_t total_tuples, size_t tuple_size, size_t chunk_size) {
    if (!input_data || total_tuples == 0 || tuple_size == 0 || chunk_size == 0) {
        return NULL;
    }

    if (total_tuples > SIZE_MAX - chunk_size) {
        return NULL;
    }

    if (tuple_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    size_t num_chunks = (total_tuples + chunk_size - 1) / chunk_size;

    ChunkedData *result = (ChunkedData*)malloc(sizeof(ChunkedData));
    if (!result) {
        return NULL;
    }

    result->num_chunks = num_chunks;
    result->chunks = (Chunk*)calloc(num_chunks, sizeof(Chunk));
    if (!result->chunks) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < num_chunks; ++i) {
        size_t current_chunk_tuples = chunk_size;
        if (i == num_chunks - 1) {
            size_t remainder = total_tuples % chunk_size;
            if (remainder != 0) {
                current_chunk_tuples = remainder;
            }
        }

        if (current_chunk_tuples > SIZE_MAX / tuple_size) {
            result->num_chunks = i;
            free_chunked_data(result);
            return NULL;
        }

        size_t elements_in_chunk = current_chunk_tuples * tuple_size;
        
        if (elements_in_chunk > SIZE_MAX / sizeof(int)) {
            result->num_chunks = i;
            free_chunked_data(result);
            return NULL;
        }

        result->chunks[i].data = (int*)malloc(elements_in_chunk * sizeof(int));
        if (!result->chunks[i].data) {
            result->num_chunks = i; 
            free_chunked_data(result);
            return NULL;
        }

        result->chunks[i].num_tuples = current_chunk_tuples;
        result->chunks[i].tuple_size = tuple_size;

        size_t offset = i * chunk_size * tuple_size;
        memcpy(result->chunks[i].data, input_data + offset, elements_in_chunk * sizeof(int));
    }

    return result;
}

int main(void) {
    size_t total_tuples = 10;
    size_t tuple_size = 3;
    size_t chunk_size = 4;
    
    if (total_tuples > SIZE_MAX / tuple_size || (total_tuples * tuple_size) > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }
    
    size_t total_elements = total_tuples * tuple_size;
    int *input_data = (int*)malloc(total_elements * sizeof(int));
    if (!input_data) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < total_elements; ++i) {
        input_data[i] = (int)i;
    }

    ChunkedData *chunked = chunk_tuples(input_data, total_tuples, tuple_size, chunk_size);
    if (!chunked) {
        free(input_data);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < chunked->num_chunks; ++i) {
        printf("Chunk %zu:\n", i);
        for (size_t j = 0; j < chunked->chunks[i].num_tuples; ++j) {
            printf("  Tuple %zu: ", j);
            for (size_t k = 0; k < chunked->chunks[i].tuple_size; ++k) {
                printf("%d ", chunked->chunks[i].data[j * chunked->chunks[i].tuple_size + k]);
            }
            printf("\n");
        }
    }

    free_chunked_data(chunked);
    free(input_data);

    return EXIT_SUCCESS;
}