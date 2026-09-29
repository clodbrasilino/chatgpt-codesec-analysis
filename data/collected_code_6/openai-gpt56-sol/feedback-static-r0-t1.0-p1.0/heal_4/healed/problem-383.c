#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t toggle_odd_bits(uint32_t value)
{
    return value ^ UINT32_C(0xAAAAAAAA);
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    size_t capacity = 0;
    size_t length = 0;
    uintmax_t value;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length] = '\0';

    errno = 0;
    value = strtoumax(input, &end, 0);

    if (errno == ERANGE || end == input || value > UINT32_MAX) {
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

    if (printf("%" PRIu32 "\n",
               toggle_odd_bits((uint32_t)value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}