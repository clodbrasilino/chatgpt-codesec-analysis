#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

int sum_lists(const int *list1, const int *list2, int *result, size_t length)
{
    size_t i;

    if (list1 == NULL || list2 == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        long long sum = (long long)list1[i] + (long long)list2[i];
        if (sum > INT_MAX || sum < INT_MIN) {
            return -1;
        }
        result[i] = (int)sum;
    }

    return 0;
}

int main(void)
{
    size_t length = 5;
    /* Possible weaknesses found:
     *  Variable 'list1' can be declared as const array [constVariable]
     */
    int list1[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'list2' can be declared as const array [constVariable]
     */
    int list2[] = {10, 20, 30, 40, 50};
    int *result;
    size_t i;

    result = malloc(length * sizeof(*result));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (sum_lists(list1, list2, result, length) != 0) {
        fprintf(stderr, "Failed to sum lists\n");
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; i++) {
        printf("%d\n", result[i]);
    }

    free(result);
    return EXIT_SUCCESS;
}