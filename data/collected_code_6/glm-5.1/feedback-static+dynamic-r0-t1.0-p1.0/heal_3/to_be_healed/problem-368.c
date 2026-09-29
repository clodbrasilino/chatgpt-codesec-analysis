#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* repeat_tuple(const void* tuple, size_t tuple_size, size_t n) {
    if (tuple == NULL || tuple_size == 0) {
        return NULL;
    }

    if (n == 0) {
        void* result = malloc(1);
        return result;
    }

    size_t total_size = tuple_size * n;
    if (total_size / n != tuple_size) {
        return NULL;
    }

    void* result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    unsigned char* dest = (unsigned char*)result;
    const unsigned char* src = (const unsigned char*)tuple;

    if (tuple_size > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, tuple_size);
    }

    size_t copied = tuple_size;
    while (copied < total_size) {
        size_t remaining = total_size - copied;
        size_t chunk = (copied < remaining) ? copied : remaining;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest + copied, dest, chunk);
        copied += chunk;
    }

    return result;
}

int main() {
    int original_tuple[] = {1, 2, 3};
    size_t tuple_size = sizeof(original_tuple);
    size_t n = 4;

    int* repeated = (int*)repeat_tuple(original_tuple, tuple_size, n);
    if (repeated == NULL) {
        return 1;
    }

    size_t total_elements = (tuple_size / sizeof(int)) * n;
    for (size_t i = 0; i < total_elements; i++) {
        printf("%d ", repeated[i]);
    }
    printf("\n");

    free(repeated);
    repeated = NULL;

    return 0;
}