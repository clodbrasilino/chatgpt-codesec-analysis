#include <stdio.h>
#include <stdlib.h>

int *sum_lists(const int *list1, const int *list2, size_t size) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }

    int *result = malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        result[i] = list1[i] + list2[i];
    }

    return result;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {6, 7, 8, 9, 10};
    size_t size = sizeof(list1) / sizeof(list1[0]);

    int *sum = sum_lists(list1, list2, size);
    if (sum == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", sum[i]);
    }
    printf("\n");

    free(sum);
    sum = NULL;

    return EXIT_SUCCESS;
}