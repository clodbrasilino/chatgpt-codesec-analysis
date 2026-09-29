#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply_lists(const int *list1, const int *list2, int *result, size_t length)
{
    size_t i;

    if (list1 == NULL || list2 == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        long long product = (long long)list1[i] * (long long)list2[i];
        if (product > INT_MAX || product < INT_MIN) {
            return -2;
        }
        result[i] = (int)product;
    }

    return 0;
}

int main(void)
{
    const int list1[] = {1, 2, 3, 4, 5};
    const int list2[] = {10, 20, 30, 40, 50};
    size_t length = sizeof(list1) / sizeof(list1[0]);
    int *result;
    int status;
    size_t i;

    result = malloc(length * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = multiply_lists(list1, list2, result, length);
    if (status != 0) {
        fprintf(stderr, "Multiplication failed with error code %d\n", status);
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; i++) {
        printf("%d\n", result[i]);
    }

    free(result);
    return EXIT_SUCCESS;
}