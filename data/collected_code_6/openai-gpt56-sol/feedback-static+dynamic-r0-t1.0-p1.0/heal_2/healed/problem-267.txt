#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

static int sum_odd_squares(uint64_t n, uint64_t *result)
{
    uint64_t n_squared;
    uint64_t n_cubed;

    if (result == NULL) {
        return 0;
    }

    if (n != 0 && n > UINT64_MAX / n) {
        return 0;
    }

    n_squared = n * n;

    if (n_squared != 0 && n > UINT64_MAX / n_squared) {
        return 0;
    }

    n_cubed = n_squared * n;

    if (n_cubed > (UINT64_MAX - n) / 4) {
        return 0;
    }

    *result = (4 * n_cubed - n) / 3;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *start;
    char *number_end;
    uintmax_t value;
    uint64_t result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(start, &number_end, 10);

    if (errno == ERANGE || number_end == start || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*number_end)) {
        ++number_end;
    }

    if (*number_end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!sum_odd_squares((uint64_t)value, &result)) {
        fputs("Result out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}