#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_character(const char *input, size_t input_length, char character)
{
    size_t output_length = 0;
    size_t i;
    char *output;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        if (input[i] != character) {
            ++output_length;
        }
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    output_length = 0;

    for (i = 0; i < input_length; ++i) {
        if (input[i] != character) {
            output[output_length++] = input[i];
        }
    }

    output[output_length] = '\0';
    return output;
}

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || *length == 0) {
                free(*buffer);
                *buffer = NULL;
                return -1;
            }
            break;
        }

        if (*length == SIZE_MAX - 1) {
            free(*buffer);
            *buffer = NULL;
            return -1;
        }

        if (*length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(*buffer);
                    *buffer = NULL;
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(*buffer, new_capacity);
            if (resized == NULL) {
                free(*buffer);
                *buffer = NULL;
                return -1;
            }

            *buffer = resized;
            capacity = new_capacity;
        }

        (*buffer)[(*length)++] = (char)ch;
    }

    if (*buffer == NULL) {
        *buffer = malloc(1);
        if (*buffer == NULL) {
            return -1;
        }
    }

    (*buffer)[*length] = '\0';
    return 0;
}

static int read_character(char *character)
{
    int ch;
    int terminator;

    if (character == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = fgetc(stdin);
    if (ch == EOF || ch == '\n') {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    terminator = fgetc(stdin);
    if (terminator == EOF) {
        if (ferror(stdin)) {
            return -1;
        }
    } else if (terminator != '\n') {
        return -1;
    }

    *character = (char)ch;
    return 0;
}

int main(void)
{
    char *input;
    char *result;
    char character;
    size_t length;

    if (read_line(&input, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (read_character(&character) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    result = remove_character(input, length, character);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}