#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static bool is_lowercase_letter(unsigned char c)
{
    return c >= (unsigned char)'a' && c <= (unsigned char)'z';
}

static bool is_matching_sequence(const char *text, size_t length)
{
    if (text == NULL || length == 0U) {
        return false;
    }

    if (!is_lowercase_letter((unsigned char)text[0]) ||
        !is_lowercase_letter((unsigned char)text[length - 1U])) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        unsigned char current = (unsigned char)text[i];

        if (!is_lowercase_letter(current) && current != (unsigned char)'_') {
            return false;
        }

        if (current == (unsigned char)'_' &&
            (i == 0U ||
             i == length - 1U ||
             text[i - 1U] == '_' ||
             text[i + 1U] == '_')) {
            return false;
        }
    }

    return true;
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
               !is_lowercase_letter((unsigned char)text[i]) &&
               text[i] != '_') {
            ++i;
        }

        size_t start = i;

        while (text[i] != '\0' &&
               (is_lowercase_letter((unsigned char)text[i]) ||
                text[i] == '_')) {
            ++i;
        }

        size_t sequence_length = i - start;

        if (sequence_length > 0U &&
            is_matching_sequence(text + start, sequence_length)) {
            if (fwrite(text + start, 1U, sequence_length, stdout) !=
                    sequence_length ||
                fputc('\n', stdout) == EOF) {
                return -1;
            }

            if (count == INT_MAX) {
                return -1;
            }

            ++count;
        }
    }

    return count;
}

static bool ensure_capacity(char **buffer, size_t *capacity, size_t required)
{
    if (buffer == NULL || capacity == NULL) {
        return false;
    }

    if (required <= *capacity) {
        return true;
    }

    size_t new_capacity = *capacity == 0U ? 128U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2U;
    }

    char *new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return false;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return true;
}

static bool append_character(char **line, size_t *length, size_t *capacity,
                             unsigned char character)
{
    if (line == NULL || length == NULL || capacity == NULL ||
        *length > SIZE_MAX - 2U) {
        return false;
    }

    if (!ensure_capacity(line, capacity, *length + 2U)) {
        return false;
    }

    (*line)[*length] = (char)character;
    ++(*length);
    (*line)[*length] = '\0';

    return true;
}

static bool process_line(char **line, size_t *length, size_t *capacity)
{
    if (line == NULL || length == NULL || capacity == NULL) {
        return false;
    }

    if (!ensure_capacity(line, capacity, *length + 1U)) {
        return false;
    }

    (*line)[*length] = '\0';

    if (find_sequences(*line) < 0) {
        return false;
    }

    *length = 0U;
    (*line)[0] = '\0';

    return true;
}

int main(void)
{
    char *line = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int result = EXIT_SUCCESS;

    for (;;) {
        int input_character = fgetc(stdin);

        if (input_character == EOF) {
            if (ferror(stdin)) {
                result = EXIT_FAILURE;
            }
            break;
        }

        if (input_character == '\n') {
            if (!process_line(&line, &length, &capacity)) {
                result = EXIT_FAILURE;
                break;
            }
        } else if (!append_character(&line, &length, &capacity,
                                     (unsigned char)input_character)) {
            result = EXIT_FAILURE;
            break;
        }
    }

    if (result == EXIT_SUCCESS && length > 0U &&
        !process_line(&line, &length, &capacity)) {
        result = EXIT_FAILURE;
    }

    if (result == EXIT_SUCCESS && fflush(stdout) == EOF) {
        result = EXIT_FAILURE;
    }

    free(line);
    return result;
}