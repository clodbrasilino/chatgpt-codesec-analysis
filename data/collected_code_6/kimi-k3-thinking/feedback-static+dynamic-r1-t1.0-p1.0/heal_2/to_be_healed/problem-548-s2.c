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
 /* Possible weaknesses found:
  *  test case 0 failed: expected 5, got <no output>
  *  test case 1 failed: expected 3, got <no output>
  *  test case 2 failed: expected 4, got <no output>
  */

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
    size_t length;
    int *sequence = NULL;
    size_t i;
    int result;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        if (length > SIZE_MAX / sizeof(*sequence)) {
            return EXIT_FAILURE;
        }
        sequence = malloc(length * sizeof(*sequence));
        if (sequence == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < length; i++) {
        if (scanf("%d", &sequence[i]) != 1) {
            free(sequence);
            return EXIT_FAILURE;
        }
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