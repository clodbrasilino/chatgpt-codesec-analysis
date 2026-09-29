#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t minimum_rotations(const char *string)
{
    size_t length;
    size_t index;
    size_t candidate;

    if (string == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(string);
    if (length == 0) {
        return 0;
    }

    index = 0;
    candidate = 1;

    while (candidate < length) {
        if (string[index] == string[candidate]) {
            ++index;
            ++candidate;
        } else if (index != 0) {
            size_t fallback = index - 1;

            while (fallback > 0 &&
                   string[index] != string[fallback]) {
                --fallback;
            }

            if (string[index] == string[fallback]) {
                index = fallback + 1;
            } else {
                index = 0;
            }
        } else {
            ++candidate;
        }
    }

    {
        size_t period = length - index;

        if (length % period == 0) {
            return period;
        }
    }

    return length;
}

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *new_buffer;

            if (new_capacity <= capacity) {
                free(buffer);
                return EXIT_FAILURE;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return EXIT_FAILURE;
        }
    }

    buffer[length] = '\0';

    if (printf("%zu\n", minimum_rotations(buffer)) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}