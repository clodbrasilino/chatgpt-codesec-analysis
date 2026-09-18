#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int* interleave_lists(const int* list1, const int* list2, size_t length);

int* interleave_lists(const int* list1, const int* list2, size_t length) {
    if (list1 == NULL || list2 == NULL || length == 0) {
        return NULL;
    }

    if (length > SIZE_MAX / (2 * sizeof(int))) {
        return NULL;
    }

    int* result = malloc(2 * length * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; i++) {
        result[2 * i] = list1[i];
        result[2 * i + 1] = list2[i];
    }

    return result;
}

int main(void) {
    int list_a[] = {1, 3, 5, 7, 9};
    /* Possible weaknesses found:
     *  Variable 'list_b' can be declared as const array [constVariable]
     */
    int list_b[] = {2, 4, 6, 8, 10};
    size_t length = sizeof(list_a) / sizeof(list_a[0]);

    int* interleaved = interleave_lists(list_a, list_b, length);
    if (interleaved == NULL) {
        fprintf(stderr, "Error processing lists\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length * 2; i++) {
        printf("%d ", interleaved[i]);
    }
    printf("\n");

    free(interleaved);

    return EXIT_SUCCESS;
}