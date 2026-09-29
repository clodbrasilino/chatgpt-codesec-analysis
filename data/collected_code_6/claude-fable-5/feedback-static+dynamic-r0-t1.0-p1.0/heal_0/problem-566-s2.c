#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int digit_sum(unsigned long long n)
{
    int sum = 0;
    while (n > 0ULL) {
        sum += (int)(n % 10ULL);
        n /= 10ULL;
    }
    return sum;
}

static int parse_non_negative(const char *str, unsigned long long *out)
{
    char *endptr = NULL;
    unsigned long long value = 0ULL;

    if (str == NULL || out == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '-' || *str == '\0') {
        return -1;
    }

    errno = 0;
    value = strtoull(str, &endptr, 10);

    if (errno == ERANGE) {
        return -1;
    }

    if (endptr == str) {
        return -1;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return -1;
    }

    *out = value;
    return 0;
}

int main(void)
{
    char buffer[64];
    unsigned long long number = 0ULL;
    int result = 0;

    printf("Enter a non-negative integer: ");
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (parse_non_negative(buffer, &number) != 0) {
        fprintf(stderr, "Error: invalid non-negative integer input.\n");
        return EXIT_FAILURE;
    }

    result = digit_sum(number);

    if (printf("Digit sum of %llu is %d\n", number, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}