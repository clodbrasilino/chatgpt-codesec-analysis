#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int parity(unsigned long long number)
{
    unsigned int result = 0U;

    while (number != 0ULL) {
        result ^= 1U;
        number &= number - 1ULL;
    }

    return result;
}

int main(void)
{
    char *input;
    char *end;
    unsigned long long number;
    size_t length = 0U;
    size_t capacity = 64U;
    int ch;

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length >= capacity - 1U) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
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

    if (length == 0U) {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    errno = 0;
    number = strtoull(input, &end, 0);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid trailing characters.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%u\n", parity(number)) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}