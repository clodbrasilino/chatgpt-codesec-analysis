#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int longest_increasing_subsequence(const int *sequence, size_t count, size_t *length)
{
    int *tails;
    size_t tails_count = 0;

    if (length == NULL) {
        return -1;
    }

    *length = 0;

    if (count == 0) {
        return 0;
    }

    if (sequence == NULL || count > SIZE_MAX / sizeof(*tails)) {
        return -1;
    }

    tails = malloc(count * sizeof(*tails));
    if (tails == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t left = 0;
        size_t right = tails_count;

        while (left < right) {
            size_t middle = left + (right - left) / 2;

            if (tails[middle] < sequence[i]) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        tails[left] = sequence[i];

        if (left == tails_count) {
            ++tails_count;
        }
    }

    free(tails);
    *length = tails_count;
    return 0;
}

int main(void)
{
    int *sequence = NULL;
    size_t count;
    size_t length;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid sequence length\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*sequence)) {
        fputs("Sequence is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0) {
        sequence = malloc(count * sizeof(*sequence));
        if (sequence == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &sequence[i]) != 1) {
            fputs("Invalid sequence element\n", stderr);
            free(sequence);
            return EXIT_FAILURE;
        }
    }

    if (longest_increasing_subsequence(sequence, count, &length) != 0) {
        fputs("Unable to calculate subsequence length\n", stderr);
        free(sequence);
        return EXIT_FAILURE;
    }

    free(sequence);

    if (printf("%zu\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}