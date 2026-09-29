#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} ChunkedTuples;

int chunk_tuples(const int *array, size_t length, size_t n, ChunkedTuples *out) {
    size_t count;
    size_t i;
    if (out == NULL || n == 0) {
        return -1;
    }
    if (array == NULL && length > 0) {
        return -1;
    }
    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    out->items = NULL;
    out->count = 0;
    if (length == 0) {
        return 0;
    }
    count = length / n + (length % n != 0);
    out->items = calloc(count, sizeof(Tuple));
    if (out->items == NULL) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        size_t start = i * n;
        size_t chunk_size = length - start;
        size_t k;
        if (chunk_size > n) {
            chunk_size = n;
        }
        out->items[i].data = malloc(chunk_size * sizeof(int));
        if (out->items[i].data == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(out->items[j].data);
            }
            free(out->items);
            out->items = NULL;
            return -1;
        }
        out->items[i].size = chunk_size;
        for (k = 0; k < chunk_size; k++) {
            out->items[i].data[k] = array[start + k];
        }
    }
    out->count = count;
    return 0;
}

void free_chunked_tuples(ChunkedTuples *out) {
    size_t i;
    if (out == NULL) {
        return;
    }
    for (i = 0; i < out->count; i++) {
        free(out->items[i].data);
        out->items[i].data = NULL;
    }
    free(out->items);
    out->items = NULL;
    out->count = 0;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t length = sizeof(data) / sizeof(data[0]);
    size_t n = 3;
    ChunkedTuples chunked;
    size_t i;
    size_t j;
    if (chunk_tuples(data, length, n, &chunked) != 0) {
        fprintf(stderr, "Error: chunking failed\n");
        return EXIT_FAILURE;
    }
    for (i = 0; i < chunked.count; i++) {
        printf("(");
        for (j = 0; j < chunked.items[i].size; j++) {
            printf("%d", chunked.items[i].data[j]);
            if (j + 1 < chunked.items[i].size) {
                printf(", ");
            }
        }
        printf(")\n");
    }
    free_chunked_tuples(&chunked);
    return EXIT_SUCCESS;
}