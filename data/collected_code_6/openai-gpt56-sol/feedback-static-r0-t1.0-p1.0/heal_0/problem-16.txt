#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        if (!is_lowercase_letter(text[i]) && text[i] != '_') {
            return false;
        }

        if (text[i] == '_' &&
            (i == 0U || i + 1U >= length ||
             text[i - 1U] == '_' || text[i + 1U] == '_')) {
            return false;
        }
    }

    return true;
}

static int find_sequences(const char *text)
{
    size_t start = 0U;
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

        start = i;

        while (text[i] != '\0' &&
               (is_lowercase_letter(text[i]) || text[i] == '_')) {
            ++i;
        }

        if (i > start && is_matching_sequence(text + start, i - start)) {
            if (printf("%.*s\n", (int)(i - start), text + start) < 0) {
                return -1;
            }
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int result = EXIT_SUCCESS;

    for (;;) {
        int c = getchar();

        if (c == EOF) {
            if (ferror(stdin)) {
                result = EXIT_FAILURE;
            }
            break;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;
            char *new_line;

            if (new_capacity <= capacity) {
                result = EXIT_FAILURE;
                break;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                result = EXIT_FAILURE;
                break;
            }

            line = new_line;
            capacity = new_capacity;
        }

        if (c == '\n') {
            line[length] = '\0';
            if (find_sequences(line) < 0) {
                result = EXIT_FAILURE;
                break;
            }
            length = 0U;
        } else {
            line[length++] = (char)c;
        }
    }

    if (result == EXIT_SUCCESS && length > 0U) {
        line[length] = '\0';
        if (find_sequences(line) < 0) {
            result = EXIT_FAILURE;
        }
    }

    free(line);
    return result;
}