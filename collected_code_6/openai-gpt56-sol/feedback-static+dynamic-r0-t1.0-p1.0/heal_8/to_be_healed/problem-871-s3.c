#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define INPUT_CAPACITY 1024U

static bool read_line(char *buffer, size_t capacity, size_t *length)
{
    if (buffer == NULL || length == NULL ||
        capacity < 2U || capacity > (size_t)INT_MAX) {
        return false;
    }

    *length = 0U;
    buffer[0] = '\0';

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    size_t used = strnlen(buffer, capacity);

    if (used == capacity) {
        buffer[0] = '\0';
        return false;
    }

    if (used > 0U && buffer[used - 1U] == '\n') {
        buffer[--used] = '\0';
        if (used > 0U && buffer[used - 1U] == '\r') {
            buffer[--used] = '\0';
        }
        *length = used;
        return true;
    }

    if (feof(stdin)) {
        if (used > 0U && buffer[used - 1U] == '\r') {
            buffer[--used] = '\0';
        }
        *length = used;
        return true;
    }

    int ch;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    buffer[0] = '\0';
    return false;
}

static bool are_rotations(const char *first, size_t first_length,
                          const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    for (size_t offset = 0U; offset < first_length; ++offset) {
        size_t index = 0U;

        while (index < first_length) {
            size_t second_index = index + offset;

            if (second_index >= first_length) {
                second_index -= first_length;
            }

            if (first[index] != second[second_index]) {
                break;
            }

            ++index;
        }

        if (index == first_length) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char *first = malloc(INPUT_CAPACITY);
    char *second = malloc(INPUT_CAPACITY);

    if (first == NULL || second == NULL) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    size_t first_length;
    size_t second_length;

    if (!read_line(first, INPUT_CAPACITY, &first_length) ||
        !read_line(second, INPUT_CAPACITY, &second_length)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    puts(are_rotations(first, first_length, second, second_length)
             ? "Yes"
             : "No");

    free(first);
    free(second);
    return EXIT_SUCCESS;
}