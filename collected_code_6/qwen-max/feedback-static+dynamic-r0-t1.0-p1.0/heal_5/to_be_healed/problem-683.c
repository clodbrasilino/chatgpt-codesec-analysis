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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:11930,execs:1663,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *endptr;
        long n = strtol(input, &endptr, 10);
        if (*endptr != '\0' && (!isspace(*endptr) || endptr == input)) {
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