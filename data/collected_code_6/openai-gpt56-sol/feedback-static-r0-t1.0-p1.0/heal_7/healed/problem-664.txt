#include <ctype.h>
#include <errno.h>
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
    char input[128];
    char *end;
    int ch;

    if (limit == NULL) {
        return 0;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs(ferror(stdin) ? "Failed to read input.\n" : "Invalid input.\n",
              stderr);
        return 0;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end == '\n') {
        *end = '\0';
    } else {
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return 0;
        }

        if (ch == EOF && ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 0;
        }
    }

    end = input;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '-') {
        fputs("Invalid input.\n", stderr);
        return 0;
    }

    errno = 0;
    *limit = strtoull(end, &end, 10);

    if (errno == ERANGE) {
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