#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_digits(uintmax_t value, uintmax_t *result)
{
    uintmax_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    do {
        sum += value % UINTMAX_C(10);
        value /= UINTMAX_C(10);
    } while (value != 0);

    *result = sum;
    return 0;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t value;
    uintmax_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (input[0] != '\0' && input[0] != '\n') {
        size_t length = 0;

        while (length < sizeof input && input[length] != '\0' &&
               input[length] != '\n') {
            ++length;
        }

        if (length == sizeof input || input[length] != '\n') {
            int ch = getchar();

            if (ch != '\n' && ch != EOF) {
                while ((ch = getchar()) != '\n' && ch != EOF) {
                }
                return EXIT_FAILURE;
            }
        }
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    {
        const char *p = input;

        while (*p == ' ' || *p == '\t' || *p == '\n' ||
               *p == '\r' || *p == '\f' || *p == '\v') {
            ++p;
        }

        if (*p == '-') {
            return EXIT_FAILURE;
        }
    }

    if (sum_digits(value, &sum) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}