#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static bool is_lowercase_letter(unsigned char c)
{
    return c >= (unsigned char)'a' && c <= (unsigned char)'z';
}

static bool is_matching_sequence(const char *text, size_t length)
{
    size_t i;

    if (text == NULL || length == 0U) {
        return false;
    }

    if (!is_lowercase_letter((unsigned char)text[0]) ||
        !is_lowercase_letter((unsigned char)text[length - 1U])) {
        return false;
    }

    for (i = 0U; i < length; ++i) {
        unsigned char c = (unsigned char)text[i];

        if (is_lowercase_letter(c)) {
            continue;
        }

        if (c != (unsigned char)'_' ||
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

    if (fwrite(text, sizeof(*text), length, stdout) != length) {
        return -1;
    }

    return fputc('\n', stdout) == EOF ? -1 : 0;
}

static int find_sequences(const char *text)
{
    size_t i = 0U;
    int count = 0;

    if (text == NULL) {
        return -1;
    }

    while (text[i] != '\0') {
        size_t start;
        size_t length;

        while (text[i] != '\0' &&
               !is_lowercase_letter((unsigned char)text[i]) &&
               text[i] != '_') {
            ++i;
        }

        if (text[i] == '\0') {
            break;
        }

        start = i;

        while (text[i] != '\0' &&
               (is_lowercase_letter((unsigned char)text[i]) ||
                text[i] == '_')) {
            ++i;
        }

        length = i - start;

        if (is_matching_sequence(text + start, length)) {
            if (count == INT_MAX ||
                print_sequence(text + start, length) != 0) {
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

    if (new_capacity < required) {
        return -1;
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
                            unsigned char character)
{
    size_t required;

    if (buffer == NULL || length == NULL || capacity == NULL) {
        return -1;
    }

    if (*length > SIZE_MAX - 2U) {
        return -1;
    }

    required = *length + 2U;

    if (grow_buffer(buffer, capacity, required) != 0) {
        return -1;
    }

    (*buffer)[*length] = (char)character;
    ++*length;
    (*buffer)[*length] = '\0';

    return 0;
}

static int process_line(char *line, size_t *length)
{
    if (line == NULL || length == NULL) {
        return -1;
    }

    if (*length > 0U && line[*length - 1U] == '\r') {
        --*length;
        line[*length] = '\0';
    }

    return find_sequences(line) < 0 ? -1 : 0;
}

int main(void)
{
    char *line = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int result = EXIT_SUCCESS;
    int character;

    if (grow_buffer(&line, &capacity, 1U) != 0) {
        return EXIT_FAILURE;
    }

    line[0] = '\0';

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            if (process_line(line, &length) != 0) {
                result = EXIT_FAILURE;
                break;
            }

            length = 0U;
            line[0] = '\0';
        } else if (append_character(&line,
                                    &length,
                                    &capacity,
                                    (unsigned char)character) != 0) {
            result = EXIT_FAILURE;
            break;
        }
    }

    if (result == EXIT_SUCCESS && ferror(stdin)) {
        result = EXIT_FAILURE;
    }

    if (result == EXIT_SUCCESS && length > 0U &&
        process_line(line, &length) != 0) {
        result = EXIT_FAILURE;
    }

    if (result == EXIT_SUCCESS && fflush(stdout) == EOF) {
        result = EXIT_FAILURE;
    }

    free(line);
    return result;
}