#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_space_char(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int sum_even_factors(uint64_t number, uint64_t *sum)
{
    uint64_t total = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (uint64_t divisor = 1; divisor <= number / divisor; ++divisor) {
        uint64_t quotient;

        if (number % divisor != 0) {
            continue;
        }

        quotient = number / divisor;

        if ((divisor & UINT64_C(1)) == 0) {
            if (divisor > UINT64_MAX - total) {
                return 0;
            }
            total += divisor;
        }

        if (quotient != divisor && (quotient & UINT64_C(1)) == 0) {
            if (quotient > UINT64_MAX - total) {
                return 0;
            }
            total += quotient;
        }
    }

    *sum = total;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;
    char *start;
    char *end;
    uintmax_t parsed;
    uint64_t sum;
    int status = EXIT_FAILURE;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            fputs("Input is too long.\n", stderr);
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    fputs("Input is too long.\n", stderr);
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    if (ch == EOF && length == 0) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    if (length == SIZE_MAX) {
        fputs("Input is too long.\n", stderr);
        goto cleanup;
    }

    if (length + 1 > capacity) {
        char *resized = realloc(input, length + 1);

        if (resized == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            goto cleanup;
        }

        input = resized;
        capacity = length + 1;
    }

    input[length] = '\0';
    start = input;

    while (is_space_char(*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        fputs("Invalid positive integer.\n", stderr);
        goto cleanup;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed == 0 ||
        parsed > UINT64_MAX) {
        fputs("Invalid positive integer.\n", stderr);
        goto cleanup;
    }

    while (is_space_char(*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid positive integer.\n", stderr);
        goto cleanup;
    }

    if (!sum_even_factors((uint64_t)parsed, &sum)) {
        fputs("Unable to calculate the sum.\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}