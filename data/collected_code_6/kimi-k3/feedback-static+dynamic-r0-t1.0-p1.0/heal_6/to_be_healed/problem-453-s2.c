#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

long long sum_even_factors(long long n)
{
    long long sum = 0;
    long long i;
    long long abs_n;

    if (n == 0) {
        return 0;
    }

    abs_n = (n < 0) ? -n : n;

    if (abs_n % 2 != 0) {
        return 0;
    }

    for (i = 2; i <= abs_n / 2; i += 2) {
        if (abs_n % i == 0) {
            if (sum > LLONG_MAX - i) {
                return -1;
            }
            sum += i;
        }
    }

    if (sum > LLONG_MAX - abs_n) {
        return -1;
    }
    sum += abs_n;

    return sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *endptr;
    long long number;
    long long result;
    size_t len;
    bool newline_found = false;

    printf("Enter a number: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    
    if (len > 0 && input[len - 1] == '\n') {
        newline_found = true;
    }
    
    if (len == sizeof(input) - 1 && !newline_found) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoll(input, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == input) {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n') {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        return EXIT_FAILURE;
    }

    result = sum_even_factors(number);

    if (result == -1) {
        fprintf(stderr, "Overflow occurred during calculation\n");
        return EXIT_FAILURE;
    }

    printf("Sum of even factors of %lld is: %lld\n", number, result);

    return EXIT_SUCCESS;
}