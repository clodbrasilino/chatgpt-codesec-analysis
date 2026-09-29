#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int is_leap_year(long long year)
{
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

static int odd_days_in_year(long long year)
{
    return is_leap_year(year) ? 2 : 1;
}

int main(void)
{
    char input[128];
    char *end;
    long long year;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the year.\n");
        return EXIT_FAILURE;
    }

    if (input[0] != '\0') {
        size_t length = 0;

        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] != '\n' && !feof(stdin)) {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            fprintf(stderr, "Input is too long.\n");
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    year = strtoll(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fprintf(stderr, "Invalid year.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if ((*end != '\n' && *end != '\0') || year <= 0) {
        fprintf(stderr, "Invalid year.\n");
        return EXIT_FAILURE;
    }

    if (*end == '\n') {
        ++end;
        if (*end != '\0') {
            fprintf(stderr, "Invalid year.\n");
            return EXIT_FAILURE;
        }
    }

    printf("%d\n", odd_days_in_year(year));
    return EXIT_SUCCESS;
}