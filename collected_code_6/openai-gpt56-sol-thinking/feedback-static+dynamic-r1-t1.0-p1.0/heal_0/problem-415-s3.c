#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

bool find_highest_product_pair(const int *array, size_t length,
                               int *first, int *second, int64_t *product)
{
    if (array == NULL || first == NULL || second == NULL ||
        product == NULL || length < 2U) {
        return false;
    }

    int max1 = array[0];
    int max2 = array[1];
    int min1 = array[0];
    int min2 = array[1];

    if (max1 < max2) {
        int temporary = max1;
        max1 = max2;
        max2 = temporary;
    }

    if (min1 > min2) {
        int temporary = min1;
        min1 = min2;
        min2 = temporary;
    }

    for (size_t i = 2U; i < length; ++i) {
        int value = array[i];

        if (value > max1) {
            max2 = max1;
            max1 = value;
        } else if (value > max2) {
            max2 = value;
        }

        if (value < min1) {
            min2 = min1;
            min1 = value;
        } else if (value < min2) {
            min2 = value;
        }
    }

    int64_t maximum_product = (int64_t)max1 * (int64_t)max2;
    int64_t minimum_product = (int64_t)min1 * (int64_t)min2;

    if (minimum_product > maximum_product) {
        *first = min1;
        *second = min2;
        *product = minimum_product;
    } else {
        *first = max1;
        *second = max2;
        *product = maximum_product;
    }

    return true;
}

int main(void)
{
    const int values[] = { -10, -3, 5, 6, -2 };
    const size_t length = sizeof(values) / sizeof(values[0]);
    int first = 0;
    int second = 0;
    int64_t product = 0;

    if (!find_highest_product_pair(values, length, &first, &second, &product)) {
        fprintf(stderr, "Unable to find a pair.\n");
        return EXIT_FAILURE;
    }

    printf("Pair: %d, %d\nProduct: %" PRId64 "\n", first, second, product);

    return EXIT_SUCCESS;
}