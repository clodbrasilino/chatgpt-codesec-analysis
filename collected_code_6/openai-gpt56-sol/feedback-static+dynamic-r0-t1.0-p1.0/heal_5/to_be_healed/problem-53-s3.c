#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int first_and_last_equal(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           string[0] == string[length - 1U];
}

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 128U;
    size_t count = 0U;
    char *line;
    int character = EOF;

    if (buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0U;

    line = malloc(capacity);
    if (line == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

        if (character == '\n' || character == EOF) {
            break;
        }

        if (count + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(line);
                return 0;
            }

            new_capacity = capacity * 2U;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return 0;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[count++] = (char)character;
    }

    if (character == EOF && count == 0U) {
        free(line);
        return 0;
    }

    line[count] = '\0';
    *buffer = line;
    *length = count;

    return 1;
}

int main(void)
{
    char *string = NULL;
    size_t length = 0U;

    if (!read_line(&string, &length)) {
        return EXIT_FAILURE;
    }

    puts(first_and_last_equal(string, length) ? "Equal" : "Not equal");

    free(string);
    return EXIT_SUCCESS;
}