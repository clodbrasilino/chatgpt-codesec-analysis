#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static char *find_first_longest_even_word(const char *text)
{
    const char *word_start = NULL;
    const char *best_start = NULL;
    size_t word_length = 0;
    size_t best_length = 0;

    if (text == NULL) {
        return NULL;
    }

    for (const char *current = text;; ++current) {
        unsigned char character = (unsigned char)*current;

        if (character != '\0' && !isspace(character)) {
            if (word_start == NULL) {
                word_start = current;
            }

            if (word_length == SIZE_MAX) {
                return NULL;
            }

            ++word_length;
        } else {
            if (word_length != 0 &&
                word_length % 2 == 0 &&
                word_length > best_length) {
                best_start = word_start;
                best_length = word_length;
            }

            word_start = NULL;
            word_length = 0;

            if (character == '\0') {
                break;
            }
        }
    }

    if (best_start == NULL || best_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(best_length + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, best_start, best_length);
    result[best_length] = '\0';

    return result;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = (*capacity == 0) ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return -1;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    if (grow_buffer(&buffer, &capacity, 128) != 0) {
        return -1;
    }

    for (;;) {
        if (capacity - length < 2) {
            if (length > SIZE_MAX - 2 ||
                grow_buffer(&buffer, &capacity, length + 2) != 0) {
                free(buffer);
                return -1;
            }
        }

        size_t available = capacity - length;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        int read_size = available > (size_t)INT_MAX
                            /* Possible weaknesses found:
                             *  use of undeclared identifier 'INT_MAX'
                             */
                            ? INT_MAX
                            : (int)available;

        if (fgets(buffer + length, read_size, stream) == NULL) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            buffer[length] = '\0';
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t bytes_read = strlen(buffer + length);
        length += bytes_read;

        if (length != 0 && buffer[length - 1] == '\n') {
            buffer[--length] = '\0';
            break;
        }

        if (feof(stream)) {
            break;
        }
    }

    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *word;

    if (read_line(stdin, &input) != 0) {
        fputs("Unable to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    word = find_first_longest_even_word(input);
    free(input);

    if (word == NULL) {
        puts("No even-length word found.");
        return EXIT_SUCCESS;
    }

    puts(word);
    free(word);

    return EXIT_SUCCESS;
}