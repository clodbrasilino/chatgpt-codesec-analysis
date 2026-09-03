#include <stdio.h>
#include <stdlib.h>

int **chunk(const int *array, size_t length, size_t n, size_t *chunk_count) {
    if (chunk_count == NULL) {
        return NULL;
    }
    *chunk_count = 0;
    if (array == NULL || n == 0) {
        return NULL;
    }
    if (length == 0) {
        return NULL;
    }
    *chunk_count = length / n + (length % n != 0);
    int **chunks = malloc(*chunk_count * sizeof(*chunks));
    if (chunks == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < *chunk_count; i++) {
        size_t current_size = (i == *chunk_count - 1) ? (length - i * n) : n;
        chunks[i] = malloc(current_size * sizeof(*chunks[i]));
        if (chunks[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(chunks[j]);
            }
            free(chunks);
            return NULL;
        }
        for (size_t j = 0; j < current_size; j++) {
            chunks[i][j] = array[i * n + j];
        }
    }
    return chunks;
}

void free_chunks(int **chunks, size_t chunk_count) {
    if (chunks == NULL) {
        return;
    }
    for (size_t i = 0; i < chunk_count; i++) {
        free(chunks[i]);
    }
    free(chunks);
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(arr) / sizeof(arr[0]);
    size_t n = 2;
    size_t chunk_count = 0;
    int **chunks = chunk(arr, length, n, &chunk_count);
    if (chunks == NULL && chunk_count != 0) {
        return 1;
    }
    for (size_t i = 0; i < chunk_count; i++) {
        size_t current_size = (i == chunk_count - 1) ? (length - i * n) : n;
        for (size_t j = 0; j < current_size; j++) {
            printf("%d ", chunks[i][j]);
        }
        printf("\n");
    }
    free_chunks(chunks, chunk_count);
    return 0;
}