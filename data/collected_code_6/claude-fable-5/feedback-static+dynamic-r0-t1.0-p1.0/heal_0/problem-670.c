#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_decreasing(const int *arr, size_t len)
{
    size_t i;

    if (arr == NULL || len == 0U) {
        return false;
    }

    for (i = 1U; i < len; i++) {
        if (arr[i] >= arr[i - 1U]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int seq1[] = {9, 7, 5, 3, 1};
    int seq2[] = {10, 8, 8, 4};
    int seq3[] = {5};
    size_t len1 = sizeof(seq1) / sizeof(seq1[0]);
    size_t len2 = sizeof(seq2) / sizeof(seq2[0]);
    size_t len3 = sizeof(seq3) / sizeof(seq3[0]);

    if (is_decreasing(seq1, len1)) {
        (void)printf("Sequence 1 is decreasing\n");
    } else {
        (void)printf("Sequence 1 is not decreasing\n");
    }

    if (is_decreasing(seq2, len2)) {
        (void)printf("Sequence 2 is decreasing\n");
    } else {
        (void)printf("Sequence 2 is not decreasing\n");
    }

    if (is_decreasing(seq3, len3)) {
        (void)printf("Sequence 3 is decreasing\n");
    } else {
        (void)printf("Sequence 3 is not decreasing\n");
    }

    return 0;
}