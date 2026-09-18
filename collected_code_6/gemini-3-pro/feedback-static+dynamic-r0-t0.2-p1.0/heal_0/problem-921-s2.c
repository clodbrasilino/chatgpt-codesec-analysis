#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} Chunk;

Chunk* chunk_tuples(const int *input, size_t input_size, size_t tuple_size, size_t chunk_size, size_t *out_chunk_count) {
    if (input == NULL || out_chunk_count == NULL || tuple_size == 0 || chunk_size == 0) {
        return NULL;
    }

    size_t total_tuples = input_size / tuple_size;
    if (total_tuples == 0) {
        *out_chunk_count = 0;
        return NULL;
    }

    size_t num_chunks = (total_tuples + chunk_size - 1) / chunk_size;
    Chunk *chunks = (Chunk *)malloc(num_chunks * sizeof(Chunk));
    if (chunks == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < num_chunks; i++) {
        size_t tuples_in_this_chunk = chunk_size;
        if (i == num_chunks - 1 && total_tuples % chunk_size != 0) {
            tuples_in_this_chunk = total_tuples % chunk_size;
        }

        chunks[i].tuples = (Tuple *)malloc(tuples_in_this_chunk * sizeof(Tuple));
        if (chunks[i].tuples == NULL) {
            for (size_t j = 0; j < i; j++) {
                for (size_t k = 0; k < chunks[j].count; k++) {
                    free(chunks[j].tuples[k].data);
                }
                free(chunks[j].tuples);
            }
            free(chunks);
            return NULL;
        }
        chunks[i].count = tuples_in_this_chunk;

        for (size_t j = 0; j < tuples_in_this_chunk; j++) {
            chunks[i].tuples[j].data = (int *)malloc(tuple_size * sizeof(int));
            if (chunks[i].tuples[j].data == NULL) {
                for (size_t k = 0; k < j; k++) {
                    free(chunks[i].tuples[k].data);
                }
                free(chunks[i].tuples);
                for (size_t k = 0; k < i; k++) {
                    for (size_t l = 0; l < chunks[k].count; l++) {
                        free(chunks[k].tuples[l].data);
                    }
                    free(chunks[k].tuples);
                }
                free(chunks);
                return NULL;
            }
            chunks[i].tuples[j].size = tuple_size;
            
            size_t input_index = (i * chunk_size + j) * tuple_size;
            for (size_t k = 0; k < tuple_size; k++) {
                chunks[i].tuples[j].data[k] = input[input_index + k];
            }
        }
    }

    *out_chunk_count = num_chunks;
    return chunks;
}

void free_chunks(Chunk *chunks, size_t chunk_count) {
    if (chunks == NULL) {
        return;
    }
    for (size_t i = 0; i < chunk_count; i++) {
        if (chunks[i].tuples != NULL) {
            for (size_t j = 0; j < chunks[i].count; j++) {
                free(chunks[i].tuples[j].data);
            }
            free(chunks[i].tuples);
        }
    }
    free(chunks);
}

int main(void) {
    int input_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    size_t input_size = sizeof(input_data) / sizeof(input_data[0]);
    size_t tuple_size = 2;
    size_t chunk_size = 2;
    size_t chunk_count = 0;

    Chunk *chunks = chunk_tuples(input_data, input_size, tuple_size, chunk_size, &chunk_count);

    if (chunks != NULL) {
        for (size_t i = 0; i < chunk_count; i++) {
            printf("Chunk %zu:\n", i);
            for (size_t j = 0; j < chunks[i].count; j++) {
                printf("  Tuple %zu: (", j);
                for (size_t k = 0; k < chunks[i].tuples[j].size; k++) {
                    printf("%d%s", chunks[i].tuples[j].data[k], k < chunks[i].tuples[j].size - 1 ? ", " : "");
                }
                printf(")\n");
            }
        }
        free_chunks(chunks, chunk_count);
    } else {
        printf("Failed to chunk tuples.\n");
    }

    return 0;
}