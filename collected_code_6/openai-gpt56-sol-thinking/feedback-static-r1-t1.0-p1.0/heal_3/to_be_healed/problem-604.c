#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(char *string, size_t begin, size_t end)
{
    while (begin < end) {
        char temporary;

        --end;
        temporary = string[begin];
        string[begin] = string[end];
        string[end] = temporary;
        ++begin;
    }
}

static void reverse_words(char *string, size_t length)
{
    size_t position = 0U;

    if (string == NULL) {
        return;
    }

    reverse_range(string, 0U, length);

    while (position < length) {
        size_t word_begin;

        while (position < length &&
               isspace((unsigned char)string[position]) != 0) {
            ++position;
        }

        word_begin = position;

        while (position < length &&
               isspace((unsigned char)string[position]) == 0) {
            ++position;
        }

        reverse_range(string, word_begin, position);
    }
}

static int read_line(FILE *stream, char **result, size_t *result_length)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer;
    int character = EOF;

    if (stream == NULL || result == NULL || result_length == NULL) {
        return -1;
    }

    *result = NULL;
    *result_length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        if (length == capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF || character == '\n') {
            break;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (ferror(stream) != 0) {
        free(buffer);
        return -1;
    }

    if (character == EOF && length == 0U) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *result = buffer;
    *result_length = length;

    return 1;
}

int main(void)
{
    char *string = NULL;
    size_t length = 0U;
    int status;

    status = read_line(stdin, &string, &length);
    if (status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    reverse_words(string, length);

    if (fwrite(string, 1U, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(string);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}