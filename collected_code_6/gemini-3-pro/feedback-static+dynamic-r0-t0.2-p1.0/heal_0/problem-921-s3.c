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

Chunk* chunk_tuples(const int *input_data, size_t input_size, size_t n, size_t *out_chunk_count) {
    if (input_data == NULL || out_chunk_count == NULL || n == 0) {
        return NULL;
    }

    size_t num_tuples = input_size / n;
    if (num_tuples == 0) {
        *out_chunk_count = 0;
        return NULL;
    }

    Chunk *chunks = malloc(sizeof(Chunk));
    if (chunks == NULL) {
        return NULL;
    }

    chunks->tuples = malloc(num_tuples * sizeof(Tuple));
    if (chunks->tuples == NULL) {
        free(chunks);
        return NULL;
    }

    chunks->count = num_tuples;
    *out_chunk_count = 1;

    for (size_t i = 0; i < num_tuples; i++) {
        chunks->tuples[i].data = malloc(n * sizeof(int));
        if (chunks->tuples[i].data == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(chunks->tuples[j].data);
            }
            free(chunks->tuples);
            free(chunks);
            return NULL;
        }
        chunks->tuples[i].size = n;
        for (size_t k = 0; k < n; k++) {
            chunks->tuples[i].data[k] = input_data[i * n + k];
        }
    }

    return chunks;
}

void free_chunks(Chunk *chunks, size_t chunk_count) {
    if (chunks == NULL) {
        return;
    }

    for (size_t c = 0; c < chunk_count; c++) {
        if (chunks[c].tuples != NULL) {
            for (size_t i = 0; i < chunks[c].count; i++) {
                free(chunks[c].tuples[i].data);
            }
            free(chunks[c].tuples);
        }
    }
    free(chunks);
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t data_size = sizeof(data) / sizeof(data[0]);
    size_t tuple_size = 3;
    size_t chunk_count = 0;

    Chunk *chunks = chunk_tuples(data, data_size, tuple_size, &chunk_count);

    if (chunks != NULL) {
        for (size_t c = 0; c < chunk_count; c++) {
            for (size_t i = 0; i < chunks[c].count; i++) {
                for (size_t j = 0; j < chunks[c].tuples[i].size; j++) {
                    printf("%d ", chunks[c].tuples[i].data[j]);
                }
                printf("\n");
            }
        }
        free_chunks(chunks, chunk_count);
    }

    return 0;
}