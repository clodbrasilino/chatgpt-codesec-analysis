#include <stdio.h>
#include <stdlib.h>

int* modulo_division(const int* a, const int* b, size_t size, size_t* result_size) {
    if (size == 0) {
        *result_size = 0;
        return NULL;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t valid_size = 0;
    for (size_t i = 0; i < size; i++) {
        if (b[i] == 0) {
            continue;
        }
        result[valid_size] = a[i] % b[i];
        valid_size++;
    }

    if (valid_size == 0) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    int* trimmed_result = (int*)realloc(result, valid_size * sizeof(int));
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    *result_size = valid_size;
    return result;
}

int main() {
    const int a[] = {10, 20, 30, 40, 50};
    const int b[] = {3, 0, 7, 4, 0};
    size_t size = sizeof(a) / sizeof(a[0]);
    size_t result_size = 0;

    int* result = modulo_division(a, b, size, &result_size);

    if (result != NULL) {
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No valid modulo operations could be performed.\n");
    }

    return 0;
}