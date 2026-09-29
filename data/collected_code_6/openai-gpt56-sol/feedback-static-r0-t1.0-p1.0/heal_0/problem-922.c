#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int find_highest_product_pair(const int array[], size_t length, int *first, int *second)
{
    if (array == NULL || first == NULL || second == NULL || length < 2U) {
        return 0;
    }

    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int min1 = INT_MAX;
    int min2 = INT_MAX;

    for (size_t i = 0U; i < length; ++i) {
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

    long long max_product = (long long)max1 * (long long)max2;
    long long min_product = (long long)min1 * (long long)min2;

    if (min_product > max_product) {
        *first = min1;
        *second = min2;
    } else {
        *first = max1;
        *second = max2;
    }

    return 1;
}

int main(void)
{
    int values[] = {-10, -3, 5, 6, -2};
    size_t length = sizeof(values) / sizeof(values[0]);
    int first = 0;
    int second = 0;

    if (!find_highest_product_pair(values, length, &first, &second)) {
        fputs("Unable to find a pair.\n", stderr);
        return 1;
    }

    if (printf("Pair: %d, %d\nProduct: %lld\n",
               first, second, (long long)first * (long long)second) < 0) {
        return 1;
    }

    return 0;
}