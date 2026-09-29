#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  *  test case 1 failed: expected True, got 0
  */

bool is_decreasing_trend(const int *sequence, int length) {
    for (int i = 1; i < length; ++i) {
        if (sequence[i - 1] < sequence[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int sequence[] = {5, 4, 3, 2, 1};
    int length = sizeof(sequence) / sizeof(sequence[0]);

    if (is_decreasing_trend(sequence, length)) {
        printf("The sequence is in a decreasing trend.\n");
    } else {
        printf("The sequence is not in a decreasing trend.\n");
    }

    int sequence2[] = {5, 4, 3, 3, 1};
    length = sizeof(sequence2) / sizeof(sequence2[0]);

    if (is_decreasing_trend(sequence2, length)) {
        printf("The sequence is in a decreasing trend.\n");
    } else {
        printf("The sequence is not in a decreasing trend.\n");
    }

    int sequence3[] = {5, 6, 3, 2, 1};
    length = sizeof(sequence3) / sizeof(sequence3[0]);

    if (is_decreasing_trend(sequence3, length)) {
        printf("The sequence is in a decreasing trend.\n");
    } else {
        printf("The sequence is not in a decreasing trend.\n");
    }

    return 0;
}