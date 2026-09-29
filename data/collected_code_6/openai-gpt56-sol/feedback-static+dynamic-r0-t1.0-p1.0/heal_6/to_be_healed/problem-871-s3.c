#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_CAPACITY 1024U

static bool read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U) {
        return false;
    }

    size_t length = 0U;
    int ch = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1U >= capacity) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            buffer[0] = '\0';
            return false;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';

    if (ch == EOF && length == 0U) {
        return false;
    }

    return true;
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

    if (!read_line(first, INPUT_CAPACITY) ||
        !read_line(second, INPUT_CAPACITY)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    size_t first_length = 0U;
    size_t second_length = 0U;

    while (first_length < INPUT_CAPACITY &&
           first[first_length] != '\0') {
        ++first_length;
    }

    while (second_length < INPUT_CAPACITY &&
           second[second_length] != '\0') {
        ++second_length;
    }

    bool result = are_rotations(first, first_length,
                                second, second_length);

    puts(result ? "Yes" : "No");

    free(first);
    free(second);

    return EXIT_SUCCESS;
}