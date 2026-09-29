#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  *  test case 1 failed: expected True, got 0
  */

bool has_decreasing_trend(const int *sequence, size_t length) {
    if (sequence == NULL || length < 3) {
        return false;
    }

    size_t current_streak = 1;

    for (size_t i = 1; i < length; ++i) {
        if (sequence[i] < sequence[i - 1]) {
            current_streak++;
            if (current_streak >= 3) {
                return true;
            }
        } else if (sequence[i] > sequence[i - 1]) {
            current_streak = 1;
        }
    }

    return false;
}

int main(void) {
    int seq1[] = {9, 8, 7, 6, 5};
    int seq2[] = {1, 2, 3, 4, 5};
    int seq3[] = {10, 5, 8, 3, 1};
    int seq4[] = {1, 1, 1, 1};
    int seq5[] = {10, 9};
    int seq6[] = {5};

    size_t len1 = sizeof(seq1) / sizeof(seq1[0]);
    size_t len2 = sizeof(seq2) / sizeof(seq2[0]);
    size_t len3 = sizeof(seq3) / sizeof(seq3[0]);
    size_t len4 = sizeof(seq4) / sizeof(seq4[0]);
    size_t len5 = sizeof(seq5) / sizeof(seq5[0]);
    size_t len6 = sizeof(seq6) / sizeof(seq6[0]);

    printf("%s\n", has_decreasing_trend(seq1, len1) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(seq2, len2) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(seq3, len3) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(seq4, len4) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(seq5, len5) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(seq6, len6) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(seq1, len1) ? "True" : "False");

    return 0;
}