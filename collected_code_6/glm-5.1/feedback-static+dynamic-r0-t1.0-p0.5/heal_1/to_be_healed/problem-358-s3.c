#include <stdio.h>
#include <stdlib.h>

int* modulo_division(const int* a, const int* b, size_t size, int* error) {
    if (size == 0) {
        *error = 1;
        return NULL;
    }
    if (a == NULL || b == NULL) {
        *error = 1;
        return NULL;
    }
    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        *error = 2;
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        if (b[i] == 0) {
            free(result);
            *error = 3;
            return NULL;
        }
        result[i] = a[i] % b[i];
    }
    *error = 0;
    return result;
}

int main(void) {
    int a[] = {10, 20, 30, 40, 50};
    /* Possible weaknesses found:
     *  Variable 'b' can be declared as const array [constVariable]
     */
    int b[] = {3, 4, 5, 6, 7};
    size_t size = sizeof(a) / sizeof(a[0]);
    int error = 0;
    int* result = modulo_division(a, b, size, &error);
    if (error != 0) {
        if (error == 1) {
            fprintf(stderr, "Invalid input\n");
        } else if (error == 2) {
            fprintf(stderr, "Memory allocation failed\n");
        } else if (error == 3) {
            fprintf(stderr, "Division by zero\n");
        }
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
    return EXIT_SUCCESS;
}