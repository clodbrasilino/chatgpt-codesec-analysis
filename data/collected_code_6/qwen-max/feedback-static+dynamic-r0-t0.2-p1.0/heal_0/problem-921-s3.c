#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} TupleChunk;

TupleChunk* chunk_tuples(int *tuples, size_t tuple_count, size_t n) {
    if (tuple_count == 0 || n == 0) return NULL;

    size_t chunk_count = (tuple_count + n - 1) / n;
    TupleChunk *chunks = (TupleChunk *)malloc(chunk_count * sizeof(TupleChunk));
    if (chunks == NULL) return NULL;

    for (size_t i = 0; i < chunk_count; ++i) {
        chunks[i].length = (i + 1) * n <= tuple_count ? n : tuple_count % n;
        chunks[i].data = (int *)malloc(chunks[i].length * sizeof(int));
        if (chunks[i].data == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(chunks[j].data);
            }
            free(chunks);
            return NULL;
        }
        for (size_t j = 0; j < chunks[i].length; ++j) {
            chunks[i].data[j] = tuples[i * n + j];
        }
    }

    return chunks;
}

void free_chunks(TupleChunk *chunks, size_t chunk_count) {
    for (size_t i = 0; i < chunk_count; ++i) {
        free(chunks[i].data);
    }
    free(chunks);
}

int main() {
    int tuples[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t n = 3;

    TupleChunk *chunks = chunk_tuples(tuples, tuple_count, n);
    if (chunks == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    size_t chunk_count = (tuple_count + n - 1) / n;
    for (size_t i = 0; i < chunk_count; ++i) {
        for (size_t j = 0; j < chunks[i].length; ++j) {
            printf("%d ", chunks[i].data[j]);
        }
        printf("\n");
    }

    free_chunks(chunks, chunk_count);
    return 0;
}