#include <stddef.h>
#include <stdio.h>

typedef struct {
    int first;
    int second;
} Pair;

static int find_highest_product_pair(const int *array, size_t length, Pair *result)
{
    if (array == NULL || result == NULL || length < 2U) {
        return 0;
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

    for (size_t index = 2U; index < length; ++index) {
        int value = array[index];

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

    long long maximum_product = (long long)max1 * (long long)max2;
    long long minimum_product = (long long)min1 * (long long)min2;

    if (minimum_product > maximum_product) {
        result->first = min1;
        result->second = min2;
    } else {
        result->first = max1;
        result->second = max2;
    }

    return 1;
}

int main(void)
{
    const int array[] = {1, -10, -20, 4, 3};
    const size_t length = sizeof(array) / sizeof(array[0]);
    Pair result;

    if (!find_highest_product_pair(array, length, &result)) {
        if (fputs("Unable to find a pair.\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    long long product = (long long)result.first * (long long)result.second;

    if (printf("Pair: %d, %d\nProduct: %lld\n",
               result.first, result.second, product) < 0) {
        return 1;
    }

    return 0;
}