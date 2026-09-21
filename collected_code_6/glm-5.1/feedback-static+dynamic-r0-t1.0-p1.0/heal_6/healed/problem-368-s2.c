#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* repeat_tuple(const void* tuple, size_t tuple_size, size_t tuple_count, size_t n) {
    if (tuple == NULL || tuple_size == 0 || tuple_count == 0 || n == 0) {
        return NULL;
    }

    if (tuple_count > SIZE_MAX / n) {
        return NULL;
    }

    size_t total_elements = tuple_count * n;

    if (tuple_size > SIZE_MAX / total_elements) {
        return NULL;
    }

    size_t total_size = total_elements * tuple_size;
    size_t chunk_size = tuple_count * tuple_size;

    void* result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    const unsigned char* src = (const unsigned char*)tuple;
    unsigned char* dst = (unsigned char*)result;
    size_t copied = 0;

    if (chunk_size > total_size) {
        free(result);
        return NULL;
    }

    memcpy(dst, src, chunk_size);
    copied = chunk_size;
    dst += chunk_size;

    while (copied < total_size) {
        size_t bytes_to_copy = chunk_size < (total_size - copied) ? chunk_size : (total_size - copied);
        memcpy(dst, result, bytes_to_copy);
        dst += bytes_to_copy;
        copied += bytes_to_copy;
    }

    return result;
}

int main() {
    int tuple[] = {1, 2, 3};
    size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);
    size_t n = 4;

    int* repeated = (int*)repeat_tuple(tuple, sizeof(int), tuple_count, n);
    if (repeated == NULL) {
        return 1;
    }

    for (size_t i = 0; i < tuple_count * n; i++) {
        printf("%d ", repeated[i]);
    }
    printf("\n");

    free(repeated);
    repeated = NULL;

    return 0;
}