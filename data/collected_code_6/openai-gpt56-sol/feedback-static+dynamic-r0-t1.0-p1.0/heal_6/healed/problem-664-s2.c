#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int average_of_evens(unsigned long long limit, double *average)
{
    if (average == NULL || limit == 0ULL || limit % 2ULL != 0ULL) {
        return -1;
    }

    *average = (double)(limit / 2ULL) + 1.0;
    return 0;
}

static int read_input(char **buffer)
{
    size_t capacity = 16U;
    size_t length = 0U;
    char *input;
    int ch;

    if (buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    input = malloc(capacity);

    if (input == NULL) {
        return -1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return -1;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return -1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return -1;
    }

    if (ch == EOF && length == 0U) {
        free(input);
        return 1;
    }

    input[length] = '\0';
    *buffer = input;
    return 0;
}

int main(void)
{
    char *input;
    char *start;
    char *end;
    unsigned long long limit;
    double average;
    int read_status;

    read_status = read_input(&input);

    if (read_status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_status > 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;

    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Invalid input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    limit = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        fputs("Invalid number.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (average_of_evens(limit, &average) != 0) {
        fputs("Enter a positive even number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", average) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}