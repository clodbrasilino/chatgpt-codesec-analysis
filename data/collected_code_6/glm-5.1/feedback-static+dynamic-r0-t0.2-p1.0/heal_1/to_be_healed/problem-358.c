#include <stdio.h>
#include <stdlib.h>

int* modulo_division(const int* a, const int* b, size_t size, int* result_size) {
    if (a == NULL || b == NULL || result_size == NULL || size == 0) {
        if (result_size != NULL) *result_size = 0;
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (b[i] != 0) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        *result_size = 0;
        return NULL;
    }

    int* result = (int*)malloc(valid_count * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; i++) {
        if (b[i] != 0) {
            result[index] = a[i] % b[i];
            index++;
        }
    }

    *result_size = (int)valid_count;
    return result;
}

int main(void) {
    int a[] = {10, 20, 30, 40, 50};
    /* Possible weaknesses found:
     *  Variable 'b' can be declared as const array [constVariable]
     */
    int b[] = {3, 0, 7, 4, 0};
    size_t size = sizeof(a) / sizeof(a[0]);
    int result_size = 0;

    int* result = modulo_division(a, b, size, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No valid modulo operations could be performed.\n");
    }

    return 0;
}