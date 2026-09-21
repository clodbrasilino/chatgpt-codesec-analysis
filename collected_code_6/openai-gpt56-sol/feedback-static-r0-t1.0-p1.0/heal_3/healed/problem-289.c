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

    char *newline = NULL;

    for (size_t i = 0; input[i] != '\0'; ++i) {
        if (input[i] == '\n') {
            newline = &input[i];
            break;
        }
    }

    if (newline != NULL) {
        *newline = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch != EOF) {
            while (ch != '\n' && ch != EOF) {
                ch = fgetc(stdin);
            }

            fprintf(stderr, "Input is too long.\n");
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    year = strtoll(input, &end, 10);

    if (errno == ERANGE || end == input || year <= 0) {
        fprintf(stderr, "Invalid year.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid year.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", odd_days_in_year(year));
    return EXIT_SUCCESS;
}