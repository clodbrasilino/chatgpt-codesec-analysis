#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
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

    return 0;
}