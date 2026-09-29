#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int average_of_odds(unsigned long long limit, long double *average)
{
    if (average == NULL || limit == 0 || limit % 2 == 0) {
        return -1;
    }

    *average = ((long double)limit + 1.0L) / 2.0L;
    return 0;
}

int main(void)
{
    char input[128];
    char *end;
    unsigned long long limit;
    long double average;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    char *newline = NULL;

    for (size_t i = 0; i < sizeof input; ++i) {
        if (input[i] == '\n') {
            newline = &input[i];
            break;
        }

        if (input[i] == '\0') {
            break;
        }
    }

    if (newline != NULL) {
        *newline = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (average_of_odds(limit, &average) != 0) {
        fputs("Enter a positive odd number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Average: %.2Lf\n", average) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}