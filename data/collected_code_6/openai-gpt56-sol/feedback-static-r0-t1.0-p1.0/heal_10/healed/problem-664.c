#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128

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
    char input[INPUT_SIZE];
    char *start;
    char *end;
    unsigned long long value;
    size_t length;
    int ch;

    if (limit == NULL) {
        return 0;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs(ferror(stdin) ? "Failed to read input.\n" : "Invalid input.\n",
              stderr);
        return 0;
    }

    length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }
            return 0;
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 0;
        }
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Invalid input.\n", stderr);
        return 0;
    }

    errno = 0;
    value = strtoull(start, &end, 10);

    if (start == end || errno == ERANGE || value > ULLONG_MAX) {
        fputs("Invalid input.\n", stderr);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return 0;
    }

    *limit = value;
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