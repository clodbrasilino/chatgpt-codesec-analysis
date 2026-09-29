#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_range(char *string, size_t begin, size_t end)
{
    while (begin < end) {
        char temporary = string[begin];
        string[begin] = string[end - 1U];
        string[end - 1U] = temporary;
        ++begin;
        --end;
    }
}

void reverse_words(char *string)
{
    size_t length;
    size_t position;

    if (string == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(string);
    reverse_range(string, 0U, length);

    position = 0U;
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

static int read_line(char **result)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer;
    int character;

    if (result == NULL) {
        return -1;
    }

    *result = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1U >= capacity) {
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

        buffer[length++] = (char)character;
    }

    if (ferror(stdin) != 0) {
        free(buffer);
        return -1;
    }

    if (character == EOF && length == 0U) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *result = buffer;
    return 1;
}

int main(void)
{
    char *string = NULL;
    int status = read_line(&string);

    if (status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    reverse_words(string);

    if (puts(string) == EOF) {
        free(string);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}