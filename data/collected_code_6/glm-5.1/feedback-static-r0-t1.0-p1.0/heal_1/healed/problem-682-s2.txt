#include <stdio.h>
#include <stdlib.h>

int *multiply_lists(const int *list1, const int *list2, size_t size) {
    if (size == 0) {
        return NULL;
    }

    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }

    int *result = (int *)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        result[i] = list1[i] * list2[i];
    }

    return result;
}

int main(void) {
    const int list1[] = {1, 2, 3, 4, 5};
    const int list2[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(list1) / sizeof(list1[0]);

    int *result = multiply_lists(list1, list2, size);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}