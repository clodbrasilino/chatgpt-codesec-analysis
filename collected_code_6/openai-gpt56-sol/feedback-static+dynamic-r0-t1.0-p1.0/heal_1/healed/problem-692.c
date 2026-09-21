#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int last_two_digits_of_factorial(unsigned long long n)
{
    if (n >= 10ULL) {
        return 0U;
    }

    unsigned int result = 1U;

    for (unsigned long long i = 2ULL; i <= n; ++i) {
        result = (result * (unsigned int)i) % 100U;
    }

    return result;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input too long.\n", stderr);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Memory allocation failed.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length + 1U >= capacity) {
        char *new_input = realloc(input, length + 1U);
        if (new_input == NULL) {
            free(input);
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
        input = new_input;
    }

    input[length] = '\0';

    errno = 0;
    char *end = NULL;
    unsigned long long n = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || input[0] == '-') {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    printf("%02u\n", last_two_digits_of_factorial(n));
    return EXIT_SUCCESS;
}