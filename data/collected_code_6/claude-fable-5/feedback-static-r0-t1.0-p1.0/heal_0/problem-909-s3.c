#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

static int is_palindrome(long n)
{
    long reversed = 0;
    long original = n;

    if (n < 0) {
        return 0;
    }

    while (n > 0) {
        long digit = n % 10;
        if (reversed > (LONG_MAX - digit) / 10) {
            return 0;
        }
        reversed = reversed * 10 + digit;
        n /= 10;
    }

    return reversed == original;
}

static int previous_palindrome(long n, long *result)
{
    long candidate;

    if (result == NULL) {
        return -1;
    }

    if (n <= 0) {
        return -1;
    }

    for (candidate = n - 1; candidate >= 0; candidate--) {
        if (is_palindrome(candidate)) {
            *result = candidate;
            return 0;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    long number;
    long result;
    char *endptr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    endptr = NULL;
    number = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: invalid number '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (previous_palindrome(number, &result) != 0) {
        fprintf(stderr, "Error: no previous palindrome exists for %ld\n", number);
        return EXIT_FAILURE;
    }

    if (printf("Previous palindrome of %ld is %ld\n", number, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}