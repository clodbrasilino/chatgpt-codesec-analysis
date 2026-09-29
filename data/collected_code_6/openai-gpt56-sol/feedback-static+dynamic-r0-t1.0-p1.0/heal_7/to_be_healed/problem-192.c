#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static bool has_letter_and_number(const char *string)
{
    if (string == NULL) {
        return false;
    }

    bool has_letter = false;
    bool has_number = false;

    for (; *string != '\0'; ++string) {
        unsigned char character = (unsigned char)*string;

        has_letter = has_letter || isalpha(character) != 0;
        has_number = has_number || isdigit(character) != 0;

        if (has_letter && has_number) {
            return true;
        }
    }

    return false;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (length > SIZE_MAX - 2) {
            free(buffer);
            return NULL;
        }

        size_t required = length + 2;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return NULL;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    int result = puts(has_letter_and_number(input) ? "true" : "false");

    free(input);

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}