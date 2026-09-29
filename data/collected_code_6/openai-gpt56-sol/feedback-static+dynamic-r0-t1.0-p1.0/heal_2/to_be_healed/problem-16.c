#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
 */
#include <stdint.h>

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

        {
            const size_t start = i;

            while (text[i] != '\0' &&
                   (is_lowercase_letter(text[i]) || text[i] == '_')) {
                ++i;
            }

            if (i > start && is_matching_sequence(text + start, i - start)) {
                if (fwrite(text + start, 1U, i - start, stdout) != i - start ||
                    fputc('\n', stdout) == EOF) {
                    return -1;
                }

                /* Possible weaknesses found:
                 *  'INT_MAX' undeclared (first use in this function)
                 *  each undeclared identifier is reported only once for each function it appears in
                 *  use of undeclared identifier 'INT_MAX'
                 */
                if (count == INT_MAX) {
                    return -1;
                }
                ++count;
            }
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
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char input[4096];
        size_t bytes_read = fread(input, 1U, sizeof input, stdin);

        for (size_t pos = 0U; pos < bytes_read; ++pos) {
            if (input[pos] == '\n') {
                if (line == NULL) {
                    line = malloc(1U);
                    if (line == NULL) {
                        result = EXIT_FAILURE;
                        goto cleanup;
                    }
                    capacity = 1U;
                }

                line[length] = '\0';
                if (find_sequences(line) < 0) {
                    result = EXIT_FAILURE;
                    goto cleanup;
                }
                length = 0U;
                continue;
            }

            if (length == SIZE_MAX - 1U) {
                result = EXIT_FAILURE;
                goto cleanup;
            }

            if (length + 1U >= capacity) {
                size_t required = length + 2U;
                size_t new_capacity = capacity == 0U ? 128U : capacity;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2U) {
                        new_capacity = required;
                        break;
                    }
                    new_capacity *= 2U;
                }

                char *new_line = realloc(line, new_capacity);
                if (new_line == NULL) {
                    result = EXIT_FAILURE;
                    goto cleanup;
                }

                line = new_line;
                capacity = new_capacity;
            }

            line[length++] = input[pos];
        }

        if (bytes_read < sizeof input) {
            if (ferror(stdin)) {
                result = EXIT_FAILURE;
            }
            break;
        }
    }

    if (result == EXIT_SUCCESS && length > 0U) {
        line[length] = '\0';
        if (find_sequences(line) < 0) {
            result = EXIT_FAILURE;
        }
    }

cleanup:
    free(line);
    return result;
}