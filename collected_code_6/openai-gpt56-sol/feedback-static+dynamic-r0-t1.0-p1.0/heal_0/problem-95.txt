#include <stdio.h>
#include <stdlib.h>

static int minimum_sublist_length(const int *values, size_t count, long long target, size_t *result)
{
    size_t left = 0;
    long long sum = 0;
    size_t minimum = count + 1;

    if (values == NULL || result == NULL || count == 0 || target <= 0) {
        return -1;
    }

    for (size_t right = 0; right < count; ++right) {
        if (values[right] <= 0) {
            return -1;
        }

        sum += values[right];

        while (sum >= target) {
            size_t length = right - left + 1;

            if (length < minimum) {
                minimum = length;
            }

            sum -= values[left];
            ++left;
        }
    }

    *result = minimum == count + 1 ? 0 : minimum;
    return 0;
}

int main(void)
{
    int values[] = {2, 3, 1, 2, 4, 3};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t minimum = 0;
    long long target = 7;

    if (minimum_sublist_length(values, count, target, &minimum) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", minimum);
    return EXIT_SUCCESS;
}