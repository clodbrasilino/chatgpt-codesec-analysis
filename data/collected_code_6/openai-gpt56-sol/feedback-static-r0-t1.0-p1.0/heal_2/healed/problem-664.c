#include <ctype.h>
#include <errno.h>
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
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    char *end = NULL;
    unsigned long long limit;
    long double average;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;
            char *temporary;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0U) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    errno = 0;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

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