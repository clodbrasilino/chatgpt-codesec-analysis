#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_decreasing(const int *sequence, size_t length)
{
    if (sequence == NULL || length == 0U) {
        return false;
    }

    for (size_t i = 1U; i < length; i++) {
        if (sequence[i] >= sequence[i - 1U]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int seq1[] = {9, 7, 5, 3, 1};
    int seq2[] = {5, 6, 4, 2};
    int seq3[] = {10};

    size_t len1 = sizeof(seq1) / sizeof(seq1[0]);
    size_t len2 = sizeof(seq2) / sizeof(seq2[0]);
    size_t len3 = sizeof(seq3) / sizeof(seq3[0]);

    if (printf("Sequence 1 decreasing: %s\n", is_decreasing(seq1, len1) ? "true" : "false") < 0) {
        return 1;
    }
    if (printf("Sequence 2 decreasing: %s\n", is_decreasing(seq2, len2) ? "true" : "false") < 0) {
        return 1;
    }
    if (printf("Sequence 3 decreasing: %s\n", is_decreasing(seq3, len3) ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}