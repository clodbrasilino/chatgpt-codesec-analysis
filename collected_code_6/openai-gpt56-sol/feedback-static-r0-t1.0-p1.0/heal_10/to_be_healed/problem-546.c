#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

static const char *find_last_char(const char *string, int character)
{
    const unsigned char target = (unsigned char)character;
    const char *last = NULL;

    if (string == NULL) {
        return NULL;
    }

    do {
        if ((unsigned char)*string == target) {
            last = string;
        }
    } while (*string++ != '\0');

    return last;
}

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *line;
    int input;

    if (buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    line = malloc(capacity);
    if (line == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        input = fgetc(stdin);

        if (input == '\n' || input == EOF) {
            break;
        }

        if (used > SIZE_MAX - 2) {
            free(line);
            return 0;
        }

        if (used + 1 >= capacity) {
            size_t required = used + 2;
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < required) {
                    new_capacity = required;
                }
            }

            temporary = realloc(line, new_capacity);
            if (temporary == NULL) {
                free(line);
                return 0;
            }

            line = temporary;
            capacity = new_capacity;
        }

        line[used++] = (char)(unsigned char)input;
    }

    if (input == EOF && used == 0) {
        free(line);
        return 0;
    }

    line[used] = '\0';
    *buffer = line;
    *length = used;
    return 1;
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    int character;
    const char *result;

    if (!read_line(&string, &length)) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    character = fgetc(stdin);
    if (character == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    result = find_last_char(string, character);

    if (result == NULL) {
        puts("Character not found");
    } else {
        printf("%td\n", result - string);
    }

    free(string);
    return EXIT_SUCCESS;
}