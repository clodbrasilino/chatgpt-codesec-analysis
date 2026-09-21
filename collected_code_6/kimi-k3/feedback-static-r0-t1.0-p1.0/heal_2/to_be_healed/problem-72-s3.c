#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

bool isDifferenceOfSquares(int n)
{
    if (n < 0) {
        n = -n;
    }
    return (n % 4 != 2);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    long val;

    printf("Enter a number: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Input out of range.\n");
        return EXIT_FAILURE;
    }
    if (endptr == buffer) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  'num' undeclared (first use in this function)
     *  use of undeclared identifier 'num'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    num = (int)val;

    /* Possible weaknesses found:
     *  use of undeclared identifier 'num'
     */
    if (isDifferenceOfSquares(num)) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'num'
         */
        printf("%d can be represented as difference of two squares.\n", num);
    } else {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'num'
         */
        printf("%d cannot be represented as difference of two squares.\n", num);
    }

    return EXIT_SUCCESS;
}