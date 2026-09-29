#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_in_sequence(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = UINT32_MAX;

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;

        if (middle != 0 && middle > number / middle) {
            high = middle - 1;
            continue;
        }

        uint64_t square = middle * middle;

        if (square == number) {
            return true;
        }

        low = middle + 1;
    }

    return false;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        return NULL;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(input);
                return NULL;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(input);
                errno = EOVERFLOW;
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                return NULL;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    input[length] = '\0';
    return input;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

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

    puts(is_in_sequence((uint64_t)value) ? "Present" : "Not present");

    free(input);
    return EXIT_SUCCESS;
}