#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static bool is_lowercase_letter(unsigned char character)
{
    return character >= (unsigned char)'a' &&
           character <= (unsigned char)'z';
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

    for (size_t index = 0U; index < length; ++index) {
        unsigned char current = (unsigned char)text[index];

        if (is_lowercase_letter(current)) {
            continue;
        }

        if (current != (unsigned char)'_' ||
            index == 0U ||
            index + 1U >= length ||
            text[index - 1U] == '_' ||
            text[index + 1U] == '_') {
            return false;
        }
    }

    return true;
}

static int find_sequences(const char *text)
{
    if (text == NULL) {
        return -1;
    }

    size_t index = 0U;
    int count = 0;

    while (text[index] != '\0') {
        while (text[index] != '\0' &&
               !is_lowercase_letter((unsigned char)text[index]) &&
               text[index] != '_') {
            ++index;
        }

        size_t start = index;

        while (text[index] != '\0' &&
               (is_lowercase_letter((unsigned char)text[index]) ||
                text[index] == '_')) {
            ++index;
        }

        size_t length = index - start;

        if (length != 0U &&
            is_matching_sequence(text + start, length)) {
            if (fwrite(text + start, 1U, length, stdout) != length ||
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

    size_t new_capacity = (*capacity == 0U) ? 128U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2U;
    }

    if (new_capacity < required) {
        return false;
    }

    char *new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return false;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return true;
}

static bool process_line(char **buffer, size_t *length, size_t *capacity)
{
    if (buffer == NULL || length == NULL || capacity == NULL ||
        *length == SIZE_MAX) {
        return false;
    }

    if (!ensure_capacity(buffer, capacity, *length + 1U)) {
        return false;
    }

    (*buffer)[*length] = '\0';

    if (find_sequences(*buffer) < 0) {
        return false;
    }

    *length = 0U;
    (*buffer)[0] = '\0';
    return true;
}

int main(void)
{
    char *line = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int result = EXIT_SUCCESS;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[4096];

    while (!feof(stdin)) {
        size_t bytes_read = fread(input, 1U, sizeof input, stdin);

        for (size_t index = 0U; index < bytes_read; ++index) {
            if (input[index] == (unsigned char)'\n') {
                if (!process_line(&line, &length, &capacity)) {
                    result = EXIT_FAILURE;
                    goto cleanup;
                }
            } else {
                if (length > SIZE_MAX - 2U ||
                    !ensure_capacity(&line, &capacity, length + 2U)) {
                    result = EXIT_FAILURE;
                    goto cleanup;
                }

                line[length++] = (char)input[index];
                line[length] = '\0';
            }
        }

        if (bytes_read < sizeof input) {
            if (ferror(stdin)) {
                result = EXIT_FAILURE;
            }
            break;
        }
    }

    if (result == EXIT_SUCCESS && length != 0U &&
        !process_line(&line, &length, &capacity)) {
        result = EXIT_FAILURE;
    }

    if (result == EXIT_SUCCESS && fflush(stdout) == EOF) {
        result = EXIT_FAILURE;
    }

cleanup:
    free(line);
    return result;
}