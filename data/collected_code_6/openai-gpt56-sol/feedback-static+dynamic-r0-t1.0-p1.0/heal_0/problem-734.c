#include <stdio.h>
#include <stdlib.h>

static int sum_of_subarray_products(const int *array, size_t length, long long *result)
{
    if (array == NULL || result == NULL) {
        return -1;
    }

    long long sum = 0;
    long long ending_product_sum = 0;

    for (size_t i = 0; i < length; ++i) {
        ending_product_sum = (ending_product_sum + 1) * array[i];
        sum += ending_product_sum;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    long long result;
    if (sum_of_subarray_products(array, length, &result) != 0) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}