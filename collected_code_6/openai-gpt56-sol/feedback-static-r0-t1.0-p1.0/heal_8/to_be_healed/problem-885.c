#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#define BYTE_VALUES ((size_t)UCHAR_MAX + 1U)

static bool are_isomorphic(const unsigned char *first, size_t first_length,
                           const unsigned char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char mapping[BYTE_VALUES] = {0};
    bool first_mapped[BYTE_VALUES] = {false};
    bool second_mapped[BYTE_VALUES] = {false};

    for (size_t i = 0; i < first_length; ++i) {
        size_t first_index = first[i];
        size_t second_index = second[i];

        if (first_mapped[first_index]) {
            if (mapping[first_index] != second[i]) {
                return false;
            }
        } else {
            if (second_mapped[second_index]) {
                return false;
            }

            mapping[first_index] = second[i];
            first_mapped[first_index] = true;
            second_mapped[second_index] = true;
        }
    }

    return true;
}

static int read_line(FILE *stream, unsigned char **line, size_t *length)
{
    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    size_t capacity = 128;
    unsigned char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    size_t used = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (used == capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            size_t new_capacity = capacity * 2;
            unsigned char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (unsigned char)character;
    }

    *line = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    unsigned char *first = NULL;
    unsigned char *second = NULL;
    size_t first_length = 0;
    size_t second_length = 0;

    if (read_line(stdin, &first, &first_length) != 0) {
        return EXIT_FAILURE;
    }

    if (read_line(stdin, &second, &second_length) != 0) {
        free(first);
        return EXIT_FAILURE;
    }

    bool result = are_isomorphic(first, first_length, second, second_length);

    free(first);
    free(second);

    if (puts(result ? "Isomorphic" : "Not isomorphic") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}