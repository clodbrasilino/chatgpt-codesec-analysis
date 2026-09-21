#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long centered_hexagonal(int n)
{
    if (n < 0) {
        return -1;
    }
    return 3LL * n * (n - 1) + 1;
}

int main(void)
{
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *endptr;
    long val;
    long long result;

    printf("Enter a non-negative integer n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input, &endptr, 10);
    if (errno != 0 || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return EXIT_FAILURE;
    }

    if (val < 0 || val > INT_MAX) {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }

    n = (int)val;
    result = centered_hexagonal(n);
    if (result == -1) {
        fprintf(stderr, "Invalid input: n must be non-negative\n");
        return EXIT_FAILURE;
    }

    printf("Centered hexagonal number for n = %d is %lld\n", n, result);
    return EXIT_SUCCESS;
}