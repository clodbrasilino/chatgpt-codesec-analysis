#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static size_t lower_bound(const int *array, size_t size, int target)
{
    size_t left = 0;
    size_t right = size;

    while (left < right) {
        size_t middle = left + (right - left) / 2;
        if (array[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

int longest_increasing_subsequence(const int *sequence, size_t length)
{
    int *tails;
    size_t tail_length = 0;
    size_t i;

    if (sequence == NULL || length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*tails)) {
        return -1;
    }

    tails = malloc(length * sizeof(*tails));
    if (tails == NULL) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        size_t position = lower_bound(tails, tail_length, sequence[i]);
        tails[position] = sequence[i];
        if (position == tail_length) {
            tail_length++;
        }
    }

    free(tails);
    tails = NULL;

    return (int)tail_length;
}

int main(void)
{
    int *sequence = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int value;
    int result;

    while (scanf("%d", &value) == 1) {
        if (length == capacity) {
            size_t new_capacity;
            int *grown;

            if (capacity == 0) {
                new_capacity = 16;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(sequence);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*grown)) {
                free(sequence);
                return EXIT_FAILURE;
            }

            grown = realloc(sequence, new_capacity * sizeof(*grown));
            if (grown == NULL) {
                free(sequence);
                return EXIT_FAILURE;
            }

            sequence = grown;
            capacity = new_capacity;
        }

        sequence[length] = value;
        length++;
    }

    result = longest_increasing_subsequence(sequence, length);

    free(sequence);
    sequence = NULL;

    if (result < 0) {
        fprintf(stderr, "Error: failed to compute longest increasing subsequence\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}