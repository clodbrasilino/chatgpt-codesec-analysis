#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int ch;

    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return buffer;
}

static size_t minimize_string(char *string)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t highest_frequency = 0;
    size_t read_index;
    size_t write_index = 0;
    unsigned char character_to_remove = 0;

    if (string == NULL) {
        return 0;
    }

    for (read_index = 0; string[read_index] != '\0'; ++read_index) {
        unsigned char character = (unsigned char)string[read_index];

        ++frequencies[character];
        if (frequencies[character] > highest_frequency) {
            highest_frequency = frequencies[character];
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
    char *string = read_line(stdin);
    size_t minimized_length;

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    minimized_length = minimize_string(string);
    printf("%zu\n", minimized_length);

    free(string);
    return EXIT_SUCCESS;
}