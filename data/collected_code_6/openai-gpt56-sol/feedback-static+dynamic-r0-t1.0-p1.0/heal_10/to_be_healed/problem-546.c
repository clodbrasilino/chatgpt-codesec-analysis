#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

static const char *find_last_char(const char *string, int character)
{
    if (string == NULL || character == EOF) {
        return NULL;
    }

    return strrchr(string, (unsigned char)character);
}

static int read_line(FILE *stream, char **output)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    buffer[length] = '\0';
    *output = buffer;
    return 1;
}

int main(void)
{
    char *string = NULL;
    const char *result;
    int character;

    if (!read_line(stdin, &string)) {
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