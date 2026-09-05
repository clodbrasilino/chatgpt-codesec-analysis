#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

bool is_linear(const int *sequence, size_t length) {
    if (sequence == NULL || length < 3) {
        return true;
    }

    int first_diff = sequence[1] - sequence[0];
    for (size_t i = 2; i < length; i++) {
        if (sequence[i] - sequence[i - 1] != first_diff) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int linear_seq[] = {2, 5, 8, 11, 14};
    int non_linear_seq[] = {1, 2, 4, 7};
    int short_seq[] = {1, 2};

    bool res1 = is_linear(linear_seq, sizeof(linear_seq) / sizeof(linear_seq[0]));
    bool res2 = is_linear(non_linear_seq, sizeof(non_linear_seq) / sizeof(non_linear_seq[0]));
    bool res3 = is_linear(short_seq, sizeof(short_seq) / sizeof(short_seq[0]));
    /* Possible weaknesses found:
     *  Calling function 'is_linear' returns 1
     *  Assignment 'res4=is_linear(NULL,0)', assigned value is 1
     */
    bool res4 = is_linear(NULL, 0);

    printf("Linear sequence: %s\n", res1 ? "true" : "false");
    printf("Non-linear sequence: %s\n", res2 ? "true" : "false");
    printf("Short sequence: %s\n", res3 ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'res4' is always true [knownConditionTrueFalse]
     *  Condition 'res4' is always true
     */
    printf("NULL sequence: %s\n", res4 ? "true" : "false");

    return 0;
}