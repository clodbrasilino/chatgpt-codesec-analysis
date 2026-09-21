#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* repeat_tuple(const void* tuple, size_t tuple_size, size_t n) {
    if (tuple == NULL || tuple_size == 0) {
        return NULL;
    }

    if (n == 0) {
        void* zero_result = malloc(1);
        if (zero_result == NULL) {
            return NULL;
        }
        return zero_result;
    }

    size_t total_size = tuple_size * n;
    if (total_size / n != tuple_size) {
        return NULL;
    }

    void* result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    errno_t err = memcpy_s(result, total_size, tuple, tuple_size);
    if (err != 0) {
        free(result);
        return NULL;
    }

    size_t copied = tuple_size;
    while (copied < total_size) {
        size_t next_copy = (copied < total_size - copied) ? copied : total_size - copied;
        errno_t err_inner = memcpy_s((unsigned char*)result + copied, total_size - copied, result, next_copy);
        if (err_inner != 0) {
            free(result);
            return NULL;
        }
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