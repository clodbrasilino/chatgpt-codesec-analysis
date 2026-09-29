#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(FILE *stream, char **output)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int character;

    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (character == '\0') {
            free(buffer);
            return -1;
        }

        if (length == capacity - 1) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *output = buffer;
    return 1;
}

static size_t minimize_string(char *string)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t maximum = 0;
    size_t read_index;
    size_t write_index = 0;
    unsigned char character_to_remove;

    if (string == NULL || string[0] == '\0') {
        return 0;
    }

    for (read_index = 0; string[read_index] != '\0'; ++read_index) {
        unsigned char character = (unsigned char)string[read_index];
        ++frequencies[character];
    }

    character_to_remove = (unsigned char)string[0];

    for (read_index = 0; string[read_index] != '\0'; ++read_index) {
        unsigned char character = (unsigned char)string[read_index];

        if (frequencies[character] > maximum) {
            maximum = frequencies[character];
            character_to_remove = character;
        }
    }

    for (read_index = 0; string[read_index] != '\0'; ++read_index) {
        if ((unsigned char)string[read_index] != character_to_remove) {
            string[write_index++] = string[read_index];
        }
    }

    string[write_index] = '\0';
    return write_index;
}

int main(void)
{
    char *string = NULL;
    int status = read_line(stdin, &string);

    if (status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    minimize_string(string);

    if (fputs(string, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}