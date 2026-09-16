#include <stdio.h>
#include <stdlib.h>

int longest_increasing_subsequence(const int *sequence, size_t length)
{
    int *tails;
    size_t size = 0;
    size_t i;

    if (sequence == NULL || length == 0) {
        return 0;
    }

    tails = malloc(length * sizeof(*tails));
    if (tails == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    for (i = 0; i < length; i++) {
        size_t lo = 0;
        size_t hi = size;

        while (lo < hi) {
            size_t mid = lo + (hi - lo) / 2;
            if (tails[mid] < sequence[i]) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        tails[lo] = sequence[i];
        if (lo == size) {
            size++;
        }
    }

    free(tails);
    return (int)size;
}

int main(void)
{
    int sequence[] = {10, 9, 2, 5, 3, 7, 101, 18};
    size_t length = sizeof(sequence) / sizeof(sequence[0]);
    int result;

    result = longest_increasing_subsequence(sequence, length);
    if (result < 0) {
        fprintf(stderr, "Error computing longest increasing subsequence\n");
        return EXIT_FAILURE;
    }

    printf("Length of longest increasing subsequence: %d\n", result);
    return EXIT_SUCCESS;
}