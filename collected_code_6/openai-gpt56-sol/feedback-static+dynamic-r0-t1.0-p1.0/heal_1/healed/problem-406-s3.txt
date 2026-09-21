#include <errno.h>
#include <limits.h>
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
    size_t length = 0U;
    size_t capacity = 128U;
    int character;
    char *end = NULL;
    unsigned long long value;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        char *resized;

        if (length + 1U >= capacity) {
            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            capacity *= 2U;
            resized = realloc(input, capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin) || (length == 0U && character == EOF)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    errno = 0;
    value = strtoull(input, &end, 0);

    if (errno != 0 || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
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