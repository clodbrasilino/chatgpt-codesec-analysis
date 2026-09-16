#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int find_highest_product_pair(const int array[], size_t length, int *first, int *second)
{
    if (array == NULL || first == NULL || second == NULL || length < 2) {
        return 0;
    }

    size_t best_first = 0;
    size_t best_second = 1;
    long long highest_product = (long long)array[0] * array[1];

    for (size_t i = 0; i < length - 1; ++i) {
        for (size_t j = i + 1; j < length; ++j) {
            long long product = (long long)array[i] * array[j];

            if (product > highest_product) {
                highest_product = product;
                best_first = i;
                best_second = j;
            }
        }
    }

    *first = array[best_first];
    *second = array[best_second];
    return 1;
}

int main(void)
{
    int values[] = {-10, -3, 1, 2, 5, 6};
    size_t length = sizeof(values) / sizeof(values[0]);
    int first = 0;
    int second = 0;

    if (!find_highest_product_pair(values, length, &first, &second)) {
        fputs("Unable to find a pair.\n", stderr);
        return 1;
    }

    if (printf("Pair with the highest product: %d and %d\n", first, second) < 0) {
        return 1;
    }

    return 0;
}