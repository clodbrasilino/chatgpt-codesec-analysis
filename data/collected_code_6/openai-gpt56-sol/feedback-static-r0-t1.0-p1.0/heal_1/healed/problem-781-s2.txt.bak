#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int has_odd_divisor_count(unsigned long long number)
{
    unsigned long long low = 1;
    unsigned long long high = number < UINT_MAX ? number : UINT_MAX;

    while (low <= high) {
        unsigned long long mid = low + (high - low) / 2;
        unsigned long long quotient = number / mid;

        if (mid == quotient && number % mid == 0) {
            return 1;
        }

        if (mid < quotient) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return 0;
}

int main(void)
{
    char input[128];
    char *end;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || number == 0) {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(has_odd_divisor_count(number) ? "Odd" : "Even");
    return EXIT_SUCCESS;
}