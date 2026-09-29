#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  *  include '<string.h>' or provide a declaration of 'memcpy'
  */

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

        if (text[i] == '\0') {
            break;
        }

        const size_t start = i;

        while (text[i] != '\0' &&
               (is_lowercase_letter(text[i]) || text[i] == '_')) {
            ++i;
        }

        const size_t length = i - start;

        if (is_matching_sequence(text + start, length)) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'INT_MAX'
             *  'INT_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             */
            if (length > (size_t)INT_MAX ||
                printf("%.*s\n", (int)length, text + start) < 0) {
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
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char chunk[4096];

        if (fgets(chunk, sizeof(chunk), stdin) == NULL) {
            if (ferror(stdin)) {
                result = EXIT_FAILURE;
            }
            break;
        }

        size_t chunk_length = 0U;
        while (chunk[chunk_length] != '\0') {
            ++chunk_length;
        }

        bool has_newline = chunk_length > 0U &&
                           chunk[chunk_length - 1U] == '\n';

        if (has_newline) {
            --chunk_length;
        }

        if (chunk_length > SIZE_MAX - length - 1U) {
            result = EXIT_FAILURE;
            break;
        }

        const size_t required = length + chunk_length + 1U;

        if (required > capacity) {
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
                break;
            }

            line = new_line;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         *  implicit declaration of function 'memcpy' [-Wimplicit-function-declaration]
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         *  call to undeclared library function 'memcpy' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memcpy'
         */
        memcpy(line + length, chunk, chunk_length);
        length += chunk_length;
        line[length] = '\0';

        if (has_newline) {
            if (find_sequences(line) < 0) {
                result = EXIT_FAILURE;
                break;
            }
            length = 0U;
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