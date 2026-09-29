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
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    uintmax_t number;
    uintmax_t sum;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end == '\r') {
        ++end;
    }

    if (*end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    if (sum_digits(number, &sum) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIuMAX "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}