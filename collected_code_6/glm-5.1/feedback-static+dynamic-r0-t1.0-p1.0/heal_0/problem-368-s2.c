#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* repeat_tuple(const void* tuple, size_t tuple_size, size_t tuple_count, size_t n) {
    if (tuple == NULL || tuple_size == 0 || n == 0) {
        return NULL;
    }

    size_t total_elements = tuple_count * n;
    size_t total_size = total_elements * tuple_size;

    if (total_elements / n != tuple_count) {
        return NULL;
    }

    void* result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    const unsigned char* src = (const unsigned char*)tuple;
    unsigned char* dst = (unsigned char*)result;

    for (size_t i = 0; i < n; i++) {
        memcpy(dst, src, tuple_count * tuple_size);
        dst += tuple_count * tuple_size;
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