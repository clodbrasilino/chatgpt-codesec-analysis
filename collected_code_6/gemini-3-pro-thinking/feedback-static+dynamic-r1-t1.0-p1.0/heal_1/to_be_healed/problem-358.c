#include <stdio.h>
#include <stdlib.h>

int* modulo_lists(const int* list1, const int* list2, size_t size);

int* modulo_lists(const int* list1, const int* list2, size_t size) {
    if (list1 == NULL || list2 == NULL || size == 0) {
        return NULL;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        if (list2[i] == 0) {
            free(result);
            return NULL;
        }
        result[i] = list1[i] % list2[i];
    }

    return result;
}

int main(void) {
    int list_a[] = {10, 25, 33, 42, 59};
    /* Possible weaknesses found:
     *  Variable 'list_b' can be declared as const array [constVariable]
     */
    int list_b[] = {3, 7, 5, 9, 4};
    size_t size = sizeof(list_a) / sizeof(list_a[0]);

    int* result = modulo_lists(list_a, list_b, size);

    if (result == NULL) {
        fprintf(stderr, "Error: Invalid input, allocation failure, or modulo by zero.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}