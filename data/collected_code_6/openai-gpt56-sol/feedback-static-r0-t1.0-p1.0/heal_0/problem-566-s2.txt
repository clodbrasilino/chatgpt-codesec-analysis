#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_digits(uintmax_t number, uintmax_t *result)
{
    uintmax_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    do {
        sum += number % 10U;
        number /= 10U;
    } while (number != 0U);

    *result = sum;
    return 0;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    uintmax_t number;
    uintmax_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (input[0] == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return EXIT_FAILURE;
    }

    if (sum_digits(number, &sum) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}