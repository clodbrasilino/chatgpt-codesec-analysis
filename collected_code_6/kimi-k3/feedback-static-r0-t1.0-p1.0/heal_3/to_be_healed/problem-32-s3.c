#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

long long largest_prime_factor(long long n)
{
    long long largest = -1;
    long long i;

    if (n <= 1)
        return -1;

    while (n % 2 == 0) {
        largest = 2;
        n /= 2;
    }

    for (i = 3; i <= n / i; i += 2) {
        while (n % i == 0) {
            largest = i;
            n /= i;
        }
    }

    if (n > 2)
        largest = n;

    return largest;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    long long number;
    long long result;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoll(buffer, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == buffer) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (number < 0) {
        if (number == LLONG_MIN) {
            fprintf(stderr, "Number out of range\n");
            return EXIT_FAILURE;
        }
        number = -number;
    }

    result = largest_prime_factor(number);

    if (result == -1)
        printf("No prime factors\n");
    else
        printf("%lld\n", result);

    return EXIT_SUCCESS;
}