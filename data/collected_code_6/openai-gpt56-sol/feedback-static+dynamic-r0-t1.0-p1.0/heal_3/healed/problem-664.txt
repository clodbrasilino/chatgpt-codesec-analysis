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
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    char *end;
    unsigned long long limit;
    long double average;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
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

    if (ferror(stdin)) {
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
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
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