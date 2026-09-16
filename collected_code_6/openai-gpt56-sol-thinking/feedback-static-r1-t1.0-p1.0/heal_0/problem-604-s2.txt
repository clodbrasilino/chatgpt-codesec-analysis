#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_range(char *string, size_t first, size_t last)
{
    while (last - first > 1U) {
        char temporary;

        --last;
        temporary = string[first];
        string[first] = string[last];
        string[last] = temporary;
        ++first;
    }
}

bool reverse_words(char *string)
{
    size_t length;
    size_t position;
    size_t read_position;
    size_t write_position;

    if (string == NULL) {
        return false;
    }

    length = strlen(string);
    reverse_range(string, 0U, length);

    position = 0U;
    while (position < length) {
        size_t word_start;

        while (position < length &&
               isspace((unsigned char)string[position]) != 0) {
            ++position;
        }

        word_start = position;

        while (position < length &&
               isspace((unsigned char)string[position]) == 0) {
            ++position;
        }

        reverse_range(string, word_start, position);
    }

    read_position = 0U;
    write_position = 0U;

    while (read_position < length) {
        while (read_position < length &&
               isspace((unsigned char)string[read_position]) != 0) {
            ++read_position;
        }

        if (read_position == length) {
            break;
        }

        if (write_position != 0U) {
            string[write_position++] = ' ';
        }

        while (read_position < length &&
               isspace((unsigned char)string[read_position]) == 0) {
            string[write_position++] = string[read_position++];
        }
    }

    string[write_position] = '\0';
    return true;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer;
    int character;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (length == capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stream) != 0) {
        free(buffer);
        return NULL;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *string;
    int result = EXIT_SUCCESS;

    string = read_line(stdin);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    if (!reverse_words(string)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (fputs(string, stdout) == EOF || fputc('\n', stdout) == EOF) {
        result = EXIT_FAILURE;
    }

    free(string);
    return result;
}