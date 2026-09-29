#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} Chunk;

Chunk* chunk_tuples(const int *input, size_t input_size, size_t n, size_t *num_chunks) {
    if (!input || input_size == 0 || n == 0 || !num_chunks) {
        return NULL;
    }

    size_t total_tuples = input_size / n;
    if (total_tuples == 0) {
        return NULL;
    }

    *num_chunks = total_tuples;

    Chunk *chunks = (Chunk *)malloc(*num_chunks * sizeof(Chunk));
    if (!chunks) {
        return NULL;
    }

    for (size_t i = 0; i < *num_chunks; ++i) {
        chunks[i].tuples = (Tuple *)malloc(sizeof(Tuple));
        if (!chunks[i].tuples) {
            for (size_t j = 0; j < i; ++j) {
                free(chunks[j].tuples->data);
                free(chunks[j].tuples);
            }
            free(chunks);
            return NULL;
        }

        chunks[i].tuples->data = (int *)malloc(n * sizeof(int));
        if (!chunks[i].tuples->data) {
            free(chunks[i].tuples);
            for (size_t j = 0; j < i; ++j) {
                free(chunks[j].tuples->data);
                free(chunks[j].tuples);
            }
            free(chunks);
            return NULL;
        }

        memcpy(chunks[i].tuples->data, input + (i * n), n * sizeof(int));
        chunks[i].count = 1;
    }

    return chunks;
}

void free_chunks(Chunk *chunks, size_t num_chunks) {
    if (!chunks) {
        return;
    }

    for (size_t i = 0; i < num_chunks; ++i) {
        if (chunks[i].tuples) {
            free(chunks[i].tuples->data);
            free(chunks[i].tuples);
        }
    }
    free(chunks);
}

int main(void) {
    int input_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    size_t input_size = sizeof(input_data) / sizeof(input_data[0]);
    size_t tuple_size = 3;
    size_t num_chunks = 0;

    Chunk *chunks = chunk_tuples(input_data, input_size, tuple_size, &num_chunks);
    if (!chunks) {
        fprintf(stderr, "Failed to chunk tuples.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_chunks; ++i) {
        printf("Chunk %zu: (", i);
        for (size_t j = 0; j < tuple_size; ++j) {
            printf("%d%s", chunks[i].tuples->data[j], (j < tuple_size - 1) ? ", " : "");
        }
        printf(")\n");
    }

    free_chunks(chunks, num_chunks);

    return EXIT_SUCCESS;
}