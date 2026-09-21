#define _POSIX_C_SOURCE 200809L

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
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    long long year;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        fprintf(stderr, "Failed to read the year.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 || input[length - 1] != '\n') {
        fprintf(stderr, "Invalid year.\n");
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    year = strtoll(input, &end, 10);

    if (errno == ERANGE || end == input || year <= 0) {
        fprintf(stderr, "Invalid year.\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' || end[1] != '\0') {
        fprintf(stderr, "Invalid year.\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("%d\n", odd_days_in_year(year));
    free(input);
    return EXIT_SUCCESS;
}