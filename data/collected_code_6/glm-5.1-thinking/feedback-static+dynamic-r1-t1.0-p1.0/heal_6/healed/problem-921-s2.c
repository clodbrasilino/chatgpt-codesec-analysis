#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int** chunk_tuples(const int* input, size_t input_len, size_t n, size_t* out_num_chunks) {
    if (out_num_chunks == NULL) {
        return NULL;
    }
    if (n == 0 || n > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    if (input_len == 0 || input == NULL) {
        *out_num_chunks = 0;
        return NULL;
    }
    size_t num_chunks = 1 + (input_len - 1) / n;
    if (num_chunks > SIZE_MAX / sizeof(int*)) {
        return NULL;
    }
    int** chunks = malloc(num_chunks * sizeof(int*));
    if (chunks == NULL) {
        return NULL;
    }
    size_t chunk_start = 0;
    for (size_t i = 0; i < num_chunks; i++) {
        chunks[i] = malloc(n * sizeof(int));
        if (chunks[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(chunks[j]);
            }
            free(chunks);
            return NULL;
        }
        size_t remaining = input_len - chunk_start;
        size_t chunk_len = remaining > n ? n : remaining;
        size_t copy_size = chunk_len * sizeof(int);
        size_t dest_size = n * sizeof(int);
        if (copy_size > dest_size) {
            for (size_t j = 0; j <= i; j++) {
                free(chunks[j]);
            }
            free(chunks);
            return NULL;
        }
        memcpy(chunks[i], input + chunk_start, copy_size);
        if (chunk_len < n) {
            memset(chunks[i] + chunk_len, 0, dest_size - copy_size);
        }
        chunk_start += n;
    }
    *out_num_chunks = num_chunks;
    return chunks;
}

void free_chunks(int** chunks, size_t num_chunks) {
    if (chunks == NULL) {
        return;
    }
    for (size_t i = 0; i < num_chunks; i++) {
        free(chunks[i]);
    }
    free(chunks);
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t n = 3;
    size_t num_chunks = 0;
    int** chunks = chunk_tuples(data, data_len, n, &num_chunks);
    if (chunks != NULL) {
        for (size_t i = 0; i < num_chunks; i++) {
            for (size_t j = 0; j < n; j++) {
                printf("%d ", chunks[i][j]);
            }
            printf("\n");
        }
        free_chunks(chunks, num_chunks);
    }
    return 0;
}