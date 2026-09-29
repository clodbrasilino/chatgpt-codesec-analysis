#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int average_even_numbers(unsigned long long limit,
                                long double *average)
{
    if (average == NULL || limit < 2ULL || limit % 2ULL != 0ULL) {
        return 0;
    }

    *average = ((long double)limit + 2.0L) / 2.0L;
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    unsigned long long limit;
    long double average;
    size_t length;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs(ferror(stdin) ? "Failed to read input.\n" : "Invalid input.\n",
              stderr);
        return EXIT_FAILURE;
    }

    length = 0U;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == 0U) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
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
            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
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