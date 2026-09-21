#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t find_first_max_even_word(const char *text, char *result, size_t result_size)
{
    const char *best_start = NULL;
    size_t best_length = 0;
    const char *cursor;

    if (text == NULL || result == NULL || result_size == 0) {
        return 0;
    }

    result[0] = '\0';
    cursor = text;

    while (*cursor != '\0') {
        const char *word_start;
        size_t word_length;

        while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        word_start = cursor;

        while (*cursor != '\0' && !isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        word_length = (size_t)(cursor - word_start);

        if (word_length != 0 &&
            word_length % 2 == 0 &&
            word_length > best_length) {
            best_start = word_start;
            best_length = word_length;
        }
    }

    if (best_start == NULL || best_length >= result_size) {
        return 0;
    }

    memmove(result, best_start, best_length);
    result[best_length] = '\0';

    return best_length;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        char *new_buffer;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (size_t)-1 / 2) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = capacity * 2;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    if (length + 1 > capacity) {
        char *new_buffer = realloc(buffer, length + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    char *result;
    size_t input_length;
    int status = 0;

    input = read_line(stdin);
    if (input == NULL) {
        return feof(stdin) && !ferror(stdin) ? 0 : 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    if (input_length == (size_t)-1) {
        free(input);
        return 1;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        free(input);
        return 1;
    }

    if (find_first_max_even_word(input, result, input_length + 1) > 0) {
        if (printf("%s\n", result) < 0) {
            status = 1;
        }
    }

    free(result);
    free(input);
    return status;
}