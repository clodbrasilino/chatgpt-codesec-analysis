#include <stdio.h>
#include <stdlib.h>

int longest_increasing_subsequence(const int *sequence, size_t length) {
    if (sequence == NULL || length == 0) {
        return 0;
    }

    size_t *tails = (size_t *)malloc(length * sizeof(size_t));
    if (tails == NULL) {
        return -1;
    }

    size_t max_len = 0;

    for (size_t i = 0; i < length; i++) {
        size_t low = 0;
        size_t high = max_len;

        while (low < high) {
            size_t mid = low + (high - low) / 2;
            if (sequence[tails[mid]] < sequence[i]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        tails[low] = i;

        if (low == max_len) {
            max_len++;
        }
    }

    free(tails);
    return (int)max_len;
}

int main(void) {
    int sequence[] = {10, 9, 2, 5, 3, 7, 101, 18};
    size_t length = sizeof(sequence) / sizeof(sequence[0]);

    int result = longest_increasing_subsequence(sequence, length);

    printf("%d\n", result);

    return 0;
}