#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static bool is_lowercase_letter(char c)
{
    return c >= 'a' && c <= 'z';
}

static bool is_matching_sequence(const char *text, size_t length)
{
    if (text == NULL || length == 0U) {
        return false;
    }

    if (!is_lowercase_letter(text[0]) ||
        !is_lowercase_letter(text[length - 1U])) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (is_lowercase_letter(text[i])) {
            continue;
        }

        if (text[i] != '_' ||
            i == 0U ||
            i + 1U >= length ||
            text[i - 1U] == '_' ||
            text[i + 1U] == '_') {
            return false;
        }
    }

    return true;
}

static int print_sequence(const char *text, size_t length)
{
    if (text == NULL || length == 0U) {
        return -1;
    }

    if (fwrite(text, 1U, length, stdout) != length) {
        return -1;
    }

    if (fputc('\n', stdout) == EOF) {
        return -1;
    }

    return 0;
}

static int find_sequences(const char *text)
{
    size_t i = 0U;
    int count = 0;

    if (text == NULL) {
        return -1;
    }

    while (text[i] != '\0') {
        while (text[i] != '\0' &&
               !is_lowercase_letter(text[i]) &&
               text[i] != '_') {
            ++i;
        }

        if (text[i] == '\0') {
            break;
        }

        const size_t start = i;

        while (text[i] != '\0' &&
               (is_lowercase_letter(text[i]) || text[i] == '_')) {
            ++i;
        }

        const size_t sequence_length = i - start;

        if (is_matching_sequence(text + start, sequence_length)) {
            if (count == INT_MAX ||
                print_sequence(text + start, sequence_length) != 0) {
                return -1;
            }

            ++count;
        }
    }

    return count;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || required == 0U) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity == 0U ? 128U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2U;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int append_character(char **buffer,
                            size_t *length,
                            size_t *capacity,
                            char character)
{
    if (buffer == NULL || length == NULL || capacity == NULL) {
        return -1;
    }

    if (*length > SIZE_MAX - 2U) {
        return -1;
    }

    if (grow_buffer(buffer, capacity, *length + 2U) != 0) {
        return -1;
    }

    (*buffer)[*length] = character;
    ++(*length);
    (*buffer)[*length] = '\0';

    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int result = EXIT_SUCCESS;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            if (length > 0U && line[length - 1U] == '\r') {
                --length;
                line[length] = '\0';
            }

            if (line != NULL && find_sequences(line) < 0) {
                result = EXIT_FAILURE;
                break;
            }

            length = 0U;
            if (line != NULL) {
                line[0] = '\0';
            }
        } else if (append_character(&line,
                                    &length,
                                    &capacity,
                                    (char)character) != 0) {
            result = EXIT_FAILURE;
            break;
        }
    }

    if (result == EXIT_SUCCESS && ferror(stdin)) {
        result = EXIT_FAILURE;
    }

    if (result == EXIT_SUCCESS && length > 0U) {
        if (line[length - 1U] == '\r') {
            --length;
            line[length] = '\0';
        }

        if (find_sequences(line) < 0) {
            result = EXIT_FAILURE;
        }
    }

    free(line);
    return result;
}