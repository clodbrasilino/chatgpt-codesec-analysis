#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool first_and_last_are_equal(const unsigned char *data, size_t length)
{
    return data != NULL && length > 0 && data[0] == data[length - 1];
}

static bool append_byte(unsigned char **data, size_t *length, size_t *capacity,
                        unsigned char value)
{
    unsigned char *resized;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;

    if (data == NULL || length == NULL || capacity == NULL ||
        *length > *capacity) {
        return false;
    }

    if (*length == *capacity) {
        if (*capacity == 0) {
            new_capacity = 128;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return false;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity <= *length) {
            return false;
        }

        resized = realloc(*data, new_capacity);
        if (resized == NULL) {
            return false;
        }

        *data = resized;
        *capacity = new_capacity;
    }

    (*data)[*length] = value;
    ++(*length);
    return true;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    free(input);
                    return EXIT_FAILURE;
                }
            } else if (next != '\n') {
                if (ungetc(next, stdin) == EOF) {
                    free(input);
                    return EXIT_FAILURE;
                }
            }

            break;
        }

        if (!append_byte(&input, &length, &capacity,
                         (unsigned char)character)) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (character == EOF && (ferror(stdin) || length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(first_and_last_are_equal(input, length) ? "Equal" : "Not equal") ==
        EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}