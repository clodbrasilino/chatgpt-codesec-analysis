#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int multiply_consecutive(const int *list, size_t size, long long **result, size_t *result_size)
{
    long long *temp;

    if (result == NULL || result_size == NULL) {
        return -1;
    }

    *result = NULL;
    *result_size = 0;

    if (size == 0) {
        return 0;
    }

    if (list == NULL) {
        return -1;
    }

    if (size == 1) {
        return 0;
    }

    temp = malloc((size - 1) * sizeof(*temp));
    if (temp == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size - 1; i++) {
        temp[i] = (long long)list[i] * (long long)list[i + 1];
    }

    *result = temp;
    *result_size = size - 1;

    return 0;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(list) / sizeof(list[0]);
    long long *result = NULL;
    size_t result_size = 0;
    int status;

    status = multiply_consecutive(list, size, &result, &result_size);
    if (status != 0) {
        fprintf(stderr, "Error: Failed to multiply consecutive numbers\n");
        return EXIT_FAILURE;
    }

    if (result_size == 0) {
        printf("List has fewer than 2 elements\n");
    } else {
        printf("Products of consecutive numbers: ");
        for (size_t i = 0; i < result_size; i++) {
            printf("%lld ", result[i]);
        }
        printf("\n");
    }

    free(result);
    return EXIT_SUCCESS;
}