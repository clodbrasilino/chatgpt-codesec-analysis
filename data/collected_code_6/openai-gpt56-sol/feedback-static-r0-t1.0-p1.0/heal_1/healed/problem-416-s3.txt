#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t maximum_sum(uint64_t n)
{
    if (n < 12) {
        return n;
    }

    uint64_t a = maximum_sum(n / 2);
    uint64_t b = maximum_sum(n / 3);
    uint64_t c = maximum_sum(n / 4);

    if (UINT64_MAX - a < b) {
        return UINT64_MAX;
    }

    uint64_t sum = a + b;

    if (UINT64_MAX - sum < c) {
        return UINT64_MAX;
    }

    sum += c;
    return sum > n ? sum : n;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 32 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    char *end = NULL;
    errno = 0;
    uintmax_t value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
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

    uint64_t result = maximum_sum((uint64_t)value);
    free(input);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}