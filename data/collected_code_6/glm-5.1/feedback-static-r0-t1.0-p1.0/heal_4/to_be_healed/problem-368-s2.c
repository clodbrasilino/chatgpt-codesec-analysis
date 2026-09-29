#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void* repeat_tuple(const void* tuple, size_t tuple_size, size_t tuple_count, size_t n, size_t max_total_size) {
    if (tuple == NULL || tuple_size == 0 || n == 0 || tuple_count == 0) {
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

    if (total_size > max_total_size) {
        return NULL;
    }

    void* result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    const unsigned char* src = (const unsigned char*)tuple;
    unsigned char* dst = (unsigned char*)result;
    size_t chunk_size = tuple_count * tuple_size;

    for (size_t i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
         *  did you mean 'memcpy'?
         */
        memcpy_s(dst, chunk_size, src, chunk_size);
        dst += chunk_size;
    }

    return result;
}

int main() {
    int tuple[] = {1, 2, 3};
    size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);
    size_t n = 4;
    size_t max_total_size = 1024;

    int* repeated = (int*)repeat_tuple(tuple, sizeof(int), tuple_count, n, max_total_size);
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