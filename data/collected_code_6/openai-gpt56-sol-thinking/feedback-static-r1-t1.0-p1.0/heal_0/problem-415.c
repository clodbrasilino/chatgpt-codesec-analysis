#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool find_highest_product_pair(const int32_t array[], size_t length,
                               int32_t *first, int32_t *second,
                               int64_t *product)
{
    int32_t largest;
    int32_t second_largest;
    int32_t smallest;
    int32_t second_smallest;
    int64_t largest_product;
    int64_t smallest_product;

    if (array == NULL || first == NULL || second == NULL ||
        product == NULL || length < 2U) {
        return false;
    }

    if (array[0] >= array[1]) {
        largest = array[0];
        second_largest = array[1];
        smallest = array[1];
        second_smallest = array[0];
    } else {
        largest = array[1];
        second_largest = array[0];
        smallest = array[0];
        second_smallest = array[1];
    }

    for (size_t i = 2U; i < length; ++i) {
        if (array[i] > largest) {
            second_largest = largest;
            largest = array[i];
        } else if (array[i] > second_largest) {
            second_largest = array[i];
        }

        if (array[i] < smallest) {
            second_smallest = smallest;
            smallest = array[i];
        } else if (array[i] < second_smallest) {
            second_smallest = array[i];
        }
    }

    largest_product = (int64_t)largest * second_largest;
    smallest_product = (int64_t)smallest * second_smallest;

    if (smallest_product > largest_product) {
        *first = smallest;
        *second = second_smallest;
        *product = smallest_product;
    } else {
        *first = largest;
        *second = second_largest;
        *product = largest_product;
    }

    return true;
}

int main(void)
{
    const int32_t array[] = {-10, -3, 5, 6, -2};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int32_t first;
    int32_t second;
    int64_t product;

    if (!find_highest_product_pair(array, length, &first, &second, &product)) {
        return EXIT_FAILURE;
    }

    if (printf("Pair: (%" PRId32 ", %" PRId32 ")\nProduct: %" PRId64 "\n",
               first, second, product) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}