#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_character(char *string, unsigned char character)
{
    unsigned char *source = (unsigned char *)string;
    unsigned char *destination = (unsigned char *)string;

    while (*source != '\0') {
        if (*source != character) {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int input = fgetc(stream);

        if (input == '\n') {
            break;
        }

        if (input == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        if (length + 1 == capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)input;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *string;
    char *character_line;

    string = read_line(stdin);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    character_line = read_line(stdin);
    if (character_line == NULL || character_line[0] == '\0') {
        free(character_line);
        free(string);
        return EXIT_FAILURE;
    }

    remove_character(string, (unsigned char)character_line[0]);

    if (puts(string) == EOF) {
        free(character_line);
        free(string);
        return EXIT_FAILURE;
    }

    free(character_line);
    free(string);

    return EXIT_SUCCESS;
}