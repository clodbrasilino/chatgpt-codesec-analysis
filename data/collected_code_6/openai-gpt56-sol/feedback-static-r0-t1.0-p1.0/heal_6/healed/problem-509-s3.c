#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int average_of_odds(unsigned long long limit, long double *average)
{
    if (average == NULL || limit == 0 || (limit & 1ULL) == 0) {
        return -1;
    }

    *average = ((long double)limit + 1.0L) / 2.0L;
    return 0;
}

static int read_line(char **buffer)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;

    if (buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    errno = 0;
    length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return -1;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    *buffer = line;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    unsigned long long limit;
    long double average;

    if (read_line(&input) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid number.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (average_of_odds(limit, &average) != 0) {
        fputs("Enter a positive odd number.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("Average: %.2Lf\n", average) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}