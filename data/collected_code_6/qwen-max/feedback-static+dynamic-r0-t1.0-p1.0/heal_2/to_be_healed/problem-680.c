#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

bool is_increasing_trend(const int numbers[], int length) {
    for (int i = 1; i < length; ++i) {
        if (numbers[i] <= numbers[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int length = sizeof(numbers) / sizeof(numbers[0]);

    if (is_increasing_trend(numbers, length)) {
        printf("The sequence has an increasing trend.\n");
    } else {
        printf("The sequence does not have an increasing trend.\n");
    }

    return 0;
}