#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128

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
    char input[INPUT_SIZE];
    char *start;
    char *end;
    unsigned long long limit;
    long double average;
    size_t length;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Invalid input.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] == '\0') {
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    limit = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
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