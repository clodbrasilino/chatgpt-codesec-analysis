#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool longest_increasing_subsequence(const int *sequence, size_t length,
                                    size_t *result)
{
    int *tails;
    size_t lis_length = 0;

    if (result == NULL || (sequence == NULL && length != 0)) {
        return false;
    }

    if (length == 0) {
        *result = 0;
        return true;
    }

    if (length > SIZE_MAX / sizeof(*tails)) {
        return false;
    }

    tails = malloc(length * sizeof(*tails));
    if (tails == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t left = 0;
        size_t right = lis_length;

        while (left < right) {
            size_t middle = left + (right - left) / 2;

            if (tails[middle] < sequence[i]) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        tails[left] = sequence[i];

        if (left == lis_length) {
            ++lis_length;
        }
    }

    free(tails);
    *result = lis_length;
    return true;
}

int main(void)
{
    size_t length;
    size_t result;
    int *sequence = NULL;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*sequence)) {
        return EXIT_FAILURE;
    }

    if (length != 0) {
        sequence = malloc(length * sizeof(*sequence));
        if (sequence == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &sequence[i]) != 1) {
            free(sequence);
            return EXIT_FAILURE;
        }
    }

    if (!longest_increasing_subsequence(sequence, length, &result)) {
        free(sequence);
        return EXIT_FAILURE;
    }

    free(sequence);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}