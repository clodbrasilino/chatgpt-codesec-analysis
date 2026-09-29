#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int average_even_numbers(unsigned long long limit, long double *average)
{
    if (average == NULL || limit < 2ULL || (limit & 1ULL) != 0ULL) {
        return 0;
    }

    *average = (long double)(limit / 2ULL) + 1.0L;
    return 1;
}

static int read_limit(unsigned long long *limit)
{
    char *input;
    char *end;
    unsigned long long value;
    size_t length = 0;
    size_t capacity = 64;
    int ch;

    if (limit == NULL) {
        return 0;
    }

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length >= capacity - 1) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return 0;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return 0;
    }

    if (ch == EOF && length == 0) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return 0;
    }

    input[length] = '\0';
    end = input;

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '\0' || *end == '-') {
        free(input);
        fputs("Invalid input.\n", stderr);
        return 0;
    }

    errno = 0;
    value = strtoull(end, &end, 10);

    if (errno == ERANGE) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input.\n", stderr);
        return 0;
    }

    *limit = value;
    free(input);
    return 1;
}

int main(void)
{
    unsigned long long limit;
    long double average;

    if (!read_limit(&limit)) {
        return EXIT_FAILURE;
    }

    if (!average_even_numbers(limit, &average)) {
        fputs("Enter an even number greater than or equal to 2.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Average: %Lg\n", average) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}