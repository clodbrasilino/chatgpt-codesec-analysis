#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *interleave(const int *list1, const int *list2, size_t length)
{
    if (list1 == NULL || list2 == NULL || length == 0) {
        return NULL;
    }
    if (length > SIZE_MAX / sizeof(*list1) / 2) {
        return NULL;
    }
    int *result = malloc(length * 2 * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < length; ++i) {
        result[i * 2] = list1[i];
        result[i * 2 + 1] = list2[i];
    }
    return result;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4};
    /* Possible weaknesses found:
     *  Variable 'list2' can be declared as const array [constVariable]
     */
    int list2[] = {5, 6, 7, 8};
    size_t length = sizeof(list1) / sizeof(list1[0]);

    int *merged = interleave(list1, list2, length);
    if (merged == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length * 2; ++i) {
        printf("%d ", merged[i]);
    }
    printf("\n");

    free(merged);
    return EXIT_SUCCESS;
}