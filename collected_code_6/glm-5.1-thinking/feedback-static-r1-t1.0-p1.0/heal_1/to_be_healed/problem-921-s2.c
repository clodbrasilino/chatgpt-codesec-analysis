#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** chunk_tuples(const int* input, size_t input_len, size_t n, size_t* out_num_chunks) {
    if (n == 0) {
        return NULL;
    }
    if (input_len == 0 || input == NULL) {
        *out_num_chunks = 0;
        return NULL;
    }
    size_t num_chunks = (input_len + n - 1) / n;
    int** chunks = (int**)malloc(num_chunks * sizeof(int*));
    if (chunks == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < num_chunks; i++) {
        chunks[i] = (int*)malloc(n * sizeof(int));
        if (chunks[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(chunks[j]);
            }
            free(chunks);
            return NULL;
        }
        size_t chunk_start = i * n;
        size_t chunk_len = n;
        if (chunk_start + n > input_len) {
            chunk_len = input_len - chunk_start;
            memset(chunks[i] + chunk_len, 0, (n - chunk_len) * sizeof(int));
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(chunks[i], input + chunk_start, chunk_len * sizeof(int));
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