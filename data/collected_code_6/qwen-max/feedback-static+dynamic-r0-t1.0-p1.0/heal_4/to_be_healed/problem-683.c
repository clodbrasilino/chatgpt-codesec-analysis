#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

bool isSumOfTwoSquares(long n) {
    if (n < 0) return false;
    for (long i = 0; i * i <= n; ++i) {
        long j = lround(sqrt(n - i * i));
        if (i * i + j * j == n && j * j == (n - i * i)) {
            return true;
        }
    }
    return false;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *endptr;
        long n = strtol(input, &endptr, 10);
        /* Possible weaknesses found:
         *  Condition '!isspace(*endptr)' is always false
         *  Assuming that condition '*endptr!='\n'' is not redundant
         *  Condition '!isspace(*endptr)' is always false [knownConditionTrueFalse]
         */
        if (*endptr != '\n' || endptr == input || (endptr > input && !isspace(*endptr))) {
            printf("Invalid input.\n");
            return 1;
        }
        if (isSumOfTwoSquares(n)) {
            printf("The number can be represented as the sum of two squares.\n");
        } else {
            printf("The number cannot be represented as the sum of two squares.\n");
        }
    } else {
        printf("Error reading input.\n");
        return 1;
    }
    return 0;
}