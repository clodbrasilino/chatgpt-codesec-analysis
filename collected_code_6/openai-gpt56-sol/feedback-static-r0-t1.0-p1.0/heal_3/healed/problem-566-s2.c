#include <ctype.h>
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
        sum += number % UINTMAX_C(10);
        number /= UINTMAX_C(10);
    } while (number != 0);

    *result = sum;
    return 0;
}

int main(void)
{
    char input[128];
    char *start;
    char *end;
    uintmax_t number;
    uintmax_t sum;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    for (end = input; *end != '\0' && *end != '\n'; ++end) {
    }

    if (*end != '\n') {
        if (!feof(stdin)) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);
        }
        return EXIT_FAILURE;
    }

    *end = '\0';
    start = input;

    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
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