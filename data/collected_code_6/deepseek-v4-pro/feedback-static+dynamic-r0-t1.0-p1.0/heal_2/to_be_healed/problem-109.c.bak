#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *s) {
    int n = strlen(s);
    if (n == 0) {
        return 0;
    }

    int *doubled = (int *)malloc(2 * n * sizeof(int));
    if (doubled == NULL) {
        return -1;
    }

    for (int i = 0; i < 2 * n; i++) {
        doubled[i] = s[i % n] - '0';
    }

    int max_bits = n;
    if (max_bits > 30) {
        max_bits = 30;
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        unsigned int value = 0;
        /* Possible weaknesses found:
         *  Assignment 'valid=1', assigned value is 1
         */
        int valid = 1;
        for (int j = 0; j < n; j++) {
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (j >= max_bits) {
                break;
            }
            value = (value << 1) | (unsigned int)doubled[i + j];
        }
        /* Possible weaknesses found:
         *  Condition 'valid' is always true [knownConditionTrueFalse]
         *  Condition 'valid' is always true
         */
        if (valid) {
            if (n > 30) {
                int odd = doubled[i + n - 1] & 1;
                if (odd) {
                    count++;
                }
            } else {
                if (value & 1) {
                    count++;
                }
            }
        }
    }

    free(doubled);
    return count;
}

int main(void) {
    char input[256];
    if (scanf("%255s", input) != 1) {
        return 1;
    }

    int result = count_odd_rotations(input);
    if (result < 0) {
        return 1;
    }

    printf("%d\n", result);
    return 0;
}