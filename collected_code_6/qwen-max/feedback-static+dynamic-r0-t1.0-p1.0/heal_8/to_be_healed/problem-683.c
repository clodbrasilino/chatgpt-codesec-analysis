#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

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
        errno = 0;
        long n = strtol(input, &endptr, 10);
        /* Possible weaknesses found:
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        if (*endptr != '\0' && (!isspace(*endptr) || endptr == input) || errno == ERANGE || (n == LONG_MAX && input[strlen(input) - 1] != '\n')) {
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