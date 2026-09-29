#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_digits(uintmax_t value, uintmax_t *result)
{
    uintmax_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    do {
        sum += value % 10U;
        value /= 10U;
    } while (value != 0U);

    *result = sum;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;
    uintmax_t sum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid non-negative integer\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0') {
        fprintf(stderr, "Invalid non-negative integer\n");
        return EXIT_FAILURE;
    }

    if (sum_digits(value, &sum) != 0) {
        fprintf(stderr, "Unable to calculate the sum\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", sum);
    return EXIT_SUCCESS;
}