#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static int has_odd_parity(unsigned long long value)
{
    int parity = 0;

    while (value != 0ULL) {
        parity ^= 1;
        value &= value - 1ULL;
    }

    return parity;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    char *end;
    unsigned long long value;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length == capacity) {
            if (capacity > (SIZE_MAX - 1U) / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity == 0U ? 64U : capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0U)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        char *resized;

        if (capacity == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        resized = realloc(input, capacity + 1U);
        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    value = strtoull(input, &end, 0);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%s\n",
               has_odd_parity(value) ? "Odd parity" : "Even parity") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}