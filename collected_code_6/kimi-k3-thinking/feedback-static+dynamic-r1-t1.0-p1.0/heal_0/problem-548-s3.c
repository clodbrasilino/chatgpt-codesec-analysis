#include <stdio.h>
#include <stdlib.h>

static size_t longest_increasing_subsequence(const int sequence[], size_t length, int *error)
{
    int *tails;
    size_t tail_count;
    size_t i;

    if (error == NULL) {
        return 0U;
    }

    *error = 0;

    if (length == 0U) {
        return 0U;
    }

    if (sequence == NULL) {
        *error = 1;
        return 0U;
    }

    tails = (int *)malloc(length * sizeof(*tails));
    if (tails == NULL) {
        *error = 1;
        return 0U;
    }

    tail_count = 0U;

    for (i = 0U; i < length; ++i) {
        size_t low = 0U;
        size_t high = tail_count;

        while (low < high) {
            size_t mid = low + ((high - low) / 2U);
            if (tails[mid] < sequence[i]) {
                low = mid + 1U;
            } else {
                high = mid;
            }
        }

        tails[low] = sequence[i];

        if (low == tail_count) {
            ++tail_count;
        }
    }

    free(tails);
    tails = NULL;

    return tail_count;
}

int main(void)
{
    int sequence[] = {10, 9, 2, 5, 3, 7, 101, 18};
    size_t length = sizeof(sequence) / sizeof(sequence[0]);
    int error = 0;
    size_t result;

    result = longest_increasing_subsequence(sequence, length, &error);

    if (error != 0) {
        (void)fprintf(stderr, "Error: failed to compute the longest increasing subsequence\n");
        return EXIT_FAILURE;
    }

    (void)printf("Length of longest increasing subsequence: %zu\n", result);

    return EXIT_SUCCESS;
}