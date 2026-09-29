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

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end = NULL;
    unsigned long long limit;
    double average;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(input);
            fputs("Input too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input too long.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    errno = 0;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input.\n", stderr);
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