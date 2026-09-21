#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(char *string, size_t first, size_t last)
{
    while (first < last) {
        char temporary;

        --last;
        if (first >= last) {
            break;
        }

        temporary = string[first];
        string[first] = string[last];
        string[last] = temporary;
        ++first;
    }
}

static bool reverse_words(char *string, size_t length, size_t *output_length)
{
    size_t position = 0U;
    size_t read_position = 0U;
    size_t write_position = 0U;

    if (string == NULL || output_length == NULL) {
        return false;
    }

    reverse_range(string, 0U, length);

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
    *output_length = write_position;
    return true;
}

static bool grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || *buffer == NULL || capacity == NULL) {
        return false;
    }

    if (*capacity > SIZE_MAX / 2U) {
        return false;
    }

    new_capacity = *capacity * 2U;
    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return false;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return true;
}

static char *read_line(FILE *stream, size_t *output_length)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer;
    /* Possible weaknesses found:
     *  The scope of the variable 'character' can be reduced. [variableScope]
     */
    int character;

    if (stream == NULL || output_length == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length >= capacity - 1U) {
            if (!grow_buffer(&buffer, &capacity)) {
                free(buffer);
                return NULL;
            }
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (ferror(stream) != 0) {
        free(buffer);
        return NULL;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *output_length = length;
    return buffer;
}

int main(void)
{
    char *string;
    size_t length;
    size_t output_length;
    int result = EXIT_SUCCESS;

    string = read_line(stdin, &length);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    if (!reverse_words(string, length, &output_length)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (fwrite(string, 1U, output_length, stdout) != output_length ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        result = EXIT_FAILURE;
    }

    free(string);
    return result;
}