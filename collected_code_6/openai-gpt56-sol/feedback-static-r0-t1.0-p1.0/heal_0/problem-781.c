#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int has_odd_divisor_count(unsigned long long number)
{
    unsigned long long low = 0;
    unsigned long long high = number < UINT_MAX ? number : UINT_MAX;

    while (low <= high) {
        unsigned long long middle = low + (high - low) / 2;

        if (middle != 0 && middle == number / middle &&
            number % middle == 0) {
            return 1;
        }

        if (middle != 0 && middle > number / middle) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    return 0;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || number == 0) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (has_odd_divisor_count(number)) {
        puts("Odd");
    } else {
        puts("Even");
    }

    return EXIT_SUCCESS;
}