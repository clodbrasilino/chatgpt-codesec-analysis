#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int parity(unsigned long long value)
{
    unsigned int result = 0U;

    while (value != 0ULL) {
        result ^= 1U;
        value &= value - 1ULL;
    }

    return result;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    size_t length = 0U;
    size_t capacity = 128U;
    int character = EOF;
    unsigned long long value;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    errno = 0;
    value = strtoull(input, &end, 0);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%u\n", parity(value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}