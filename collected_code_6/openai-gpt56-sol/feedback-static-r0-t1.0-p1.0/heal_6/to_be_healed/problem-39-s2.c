#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool can_rearrange_without_adjacent_duplicates(
    const unsigned char *string,
    size_t length)
{
    size_t frequencies[256] = {0};
    size_t maximum = 0;

    if (string == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = ++frequencies[string[i]];

        if (frequency > maximum) {
            maximum = frequency;
        }
    }

    return maximum <= (length + 1U) / 2U;
}

static bool read_line(unsigned char **buffer, size_t *length)
{
    size_t capacity = 128U;
    size_t used = 0U;
    unsigned char *line;

    if (buffer == NULL || length == NULL) {
        return false;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            if (character == EOF && ferror(stdin)) {
                free(line);
                return false;
            }

            if (character == EOF && used == 0U) {
                free(line);
                return false;
            }

            break;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity;
            unsigned char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(line);
                return false;
            }

            new_capacity = capacity * 2U;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return false;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[used++] = (unsigned char)character;
    }

    if (used > 0U && line[used - 1U] == '\r') {
        --used;
    }

    line[used] = '\0';
    *buffer = line;
    *length = used;
    return true;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0U;

    if (!read_line(&input, &length)) {
        return 1;
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    free(input);
    return 0;
}