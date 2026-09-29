#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

bool find_highest_product_pair(const int array[],
                               size_t length,
                               int *first,
                               int *second,
                               int64_t *product)
{
    int largest;
    int second_largest;
    int smallest;
    int second_smallest;
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

    largest_product = (int64_t)largest * (int64_t)second_largest;
    smallest_product = (int64_t)smallest * (int64_t)second_smallest;

    if (largest_product >= smallest_product) {
        *first = largest;
        *second = second_largest;
        *product = largest_product;
    } else {
        *first = smallest;
        *second = second_smallest;
        *product = smallest_product;
    }

    return true;
}

int main(void)
{
    const int array[] = {-10, -3, 5, 6, -2};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int first;
    int second;
    int64_t product;

    if (!find_highest_product_pair(array, length, &first, &second, &product)) {
        return EXIT_FAILURE;
    }

    if (printf("Pair: %d, %d\nProduct: %" PRId64 "\n",
               first, second, product) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}