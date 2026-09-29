#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  *  test case 1 failed: expected True, got 0
  */

bool has_decreasing_trend(const int *sequence, size_t length) {
    if (sequence == NULL || length <= 1) {
        return true;
    }
    for (size_t i = 1; i < length; i++) {
        if (sequence[i - 1] < sequence[i]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int *sequence = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int num;

    while (scanf("%d", &num) == 1) {
        if (length >= capacity) {
            capacity = capacity == 0 ? 16 : capacity * 2;
            int *temp = (int *)realloc(sequence, capacity * sizeof(int));
            if (!temp) {
                free(sequence);
                return EXIT_FAILURE;
            }
            sequence = temp;
        }
        sequence[length++] = num;
        
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != EOF) {
            if (isdigit(c) || c == '-' || c == '+') {
                ungetc(c, stdin);
                break;
            }
        }
    }

    if (has_decreasing_trend(sequence, length)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    free(sequence);
    return EXIT_SUCCESS;
}