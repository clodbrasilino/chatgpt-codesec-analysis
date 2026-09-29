#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int minimum_swaps(const char *first, const char *second, size_t *result)
{
    size_t length;
    size_t zero_one = 0;
    size_t one_zero = 0;

    if (first == NULL || second == NULL || result == NULL) {
        return 0;
    }

    length = strlen(first);
    if (length != strlen(second)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if ((first[i] != '0' && first[i] != '1') ||
            (second[i] != '0' && second[i] != '1')) {
            return 0;
        }

        if (first[i] == '0' && second[i] == '1') {
            ++zero_one;
        } else if (first[i] == '1' && second[i] == '0') {
            ++one_zero;
        }
    }

    if (((zero_one + one_zero) & 1U) != 0U) {
        return 0;
    }

    if (zero_one > SIZE_MAX - one_zero) {
        return 0;
    }

    *result = zero_one / 2 + one_zero / 2 + 2 * (zero_one % 2);
    return 1;
}

int main(void)
{
    char first[100001];
    char second[100001];
    size_t swaps;

    if (scanf("%100000s %100000s", first, second) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!minimum_swaps(first, second, &swaps)) {
        printf("-1\n");
        return EXIT_SUCCESS;
    }

    printf("%zu\n", swaps);
    return EXIT_SUCCESS;
}