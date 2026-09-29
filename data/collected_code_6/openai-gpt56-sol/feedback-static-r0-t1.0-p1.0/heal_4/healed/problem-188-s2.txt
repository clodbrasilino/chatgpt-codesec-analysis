#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_perfect_square(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = number < UINT32_MAX ? number : UINT32_MAX;

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;

        if (middle != 0 && middle > number / middle) {
            high = middle - 1;
        } else {
            uint64_t square = middle * middle;

            if (square == number) {
                return true;
            }

            low = middle + 1;
        }
    }

    return false;
}

static bool read_line(char **line)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    if (line == NULL) {
        return false;
    }

    *line = NULL;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return false;
                }
                new_capacity = capacity * 2;
            }

            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin) || length == 0) {
            free(buffer);
            return false;
        }
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return false;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return true;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    uintmax_t value;

    if (!read_line(&input)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
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

    puts(is_perfect_square((uint64_t)value) ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}