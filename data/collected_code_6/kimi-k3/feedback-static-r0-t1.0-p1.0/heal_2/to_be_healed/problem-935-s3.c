#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

unsigned long long sum_of_squares(int n)
{
    return (unsigned long long)n * (unsigned long long)(n + 1) * (unsigned long long)(2 * n + 1) / 6ULL;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *endptr = NULL;
    long value;
    int n;

    printf("Enter a positive integer n: ");

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fprintf(stderr, "Input error.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "Input too long.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (value < 1 || value > INT_MAX) {
        fprintf(stderr, "Input out of range.\n");
        return EXIT_FAILURE;
    }

    n = (int)value;

    if (n > 55108) {
        fprintf(stderr, "Input too large; result would overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of squares = %llu\n", sum_of_squares(n));

    return EXIT_SUCCESS;
}