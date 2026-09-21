#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* repeat_tuple(const void* tuple, size_t tuple_size, size_t n) {
    if (tuple == NULL || n == 0) {
        return NULL;
    }

    size_t total_size;
    if (tuple_size == 0 || n > SIZE_MAX / tuple_size) {
        return NULL;
    }
    total_size = tuple_size * n;

    void* result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, tuple, tuple_size);

    size_t copied = tuple_size;
    while (copied < total_size) {
        size_t remaining = total_size - copied;
        size_t next_copy = (copied < remaining) ? copied : remaining;
        memcpy((unsigned char*)result + copied, result, next_copy);
        copied += next_copy;
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