#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t size;
    size_t capacity;
} StringSet;

static void string_set_destroy(StringSet *set)
{
    if (set == NULL) {
        return;
    }

    for (size_t i = 0; i < set->size; ++i) {
        free(set->items[i]);
    }

    free(set->items);
    set->items = NULL;
    set->size = 0;
    set->capacity = 0;
}

static int string_set_contains_n(
    const StringSet *set,
    const char *word,
    size_t word_length
)
{
    if (set == NULL || word == NULL) {
        return 0;
    }

    for (size_t i = 0; i < set->size; ++i) {
        if (strncmp(set->items[i], word, word_length) == 0 &&
            set->items[i][word_length] == '\0') {
            return 1;
        }
    }

    return 0;
}

static int string_set_add_n(
    StringSet *set,
    const char *word,
    size_t word_length
)
{
    if (set == NULL || word == NULL || word_length == SIZE_MAX) {
        return -1;
    }

    if (string_set_contains_n(set, word, word_length)) {
        return 0;
    }

    if (set->size == set->capacity) {
        size_t new_capacity;

        if (set->capacity == 0) {
            new_capacity = 8;
        } else {
            if (set->capacity > SIZE_MAX / 2) {
                return -1;
            }
            new_capacity = set->capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*set->items)) {
            return -1;
        }

        char **new_items = realloc(
            set->items,
            new_capacity * sizeof(*set->items)
        );

        if (new_items == NULL) {
            return -1;
        }

        set->items = new_items;
        set->capacity = new_capacity;
    }

    char *copy = malloc(word_length + 1);

    if (copy == NULL) {
        return -1;
    }

    if (word_length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, word, word_length);
    }
    copy[word_length] = '\0';

    set->items[set->size++] = copy;
    return 1;
}

static int append_word_n(
    char **output,
    size_t *length,
    size_t *capacity,
    const char *word,
    size_t word_length
)
{
    if (output == NULL || length == NULL || capacity == NULL || word == NULL) {
        return -1;
    }

    size_t separator_length = *length == 0 ? 0 : 1;

    if (*length > SIZE_MAX - separator_length ||
        *length + separator_length > SIZE_MAX - word_length ||
        *length + separator_length + word_length > SIZE_MAX - 1) {
        return -1;
    }

    size_t required = *length + separator_length + word_length + 1;

    if (required > *capacity) {
        size_t new_capacity = *capacity == 0 ? 16 : *capacity;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }

            new_capacity *= 2;
        }

        char *new_output = realloc(*output, new_capacity);

        if (new_output == NULL) {
            return -1;
        }

        *output = new_output;
        *capacity = new_capacity;
    }

    if (separator_length != 0) {
        (*output)[(*length)++] = ' ';
    }

    if (word_length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(*output + *length, word, word_length);
        *length += word_length;
    }

    (*output)[*length] = '\0';
    return 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char *remove_duplicate_words(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    StringSet words = {0};
    char *output = NULL;
    size_t output_length = 0;
    size_t output_capacity = 0;
    const char *cursor = input;

    while (*cursor != '\0') {
        while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        const char *start = cursor;

        while (*cursor != '\0' && !isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        size_t word_length = (size_t)(cursor - start);

        if (word_length == 0) {
            continue;
        }

        int add_result = string_set_add_n(&words, start, word_length);

        if (add_result < 0 ||
            (add_result > 0 &&
             append_word_n(
                 &output,
                 &output_length,
                 &output_capacity,
                 start,
                 word_length
             ) != 0)) {
            string_set_destroy(&words);
            free(output);
            return NULL;
        }
    }

    string_set_destroy(&words);

    if (output == NULL) {
        output = malloc(1);

        if (output == NULL) {
            return NULL;
        }

        output[0] = '\0';
    }

    return output;
}

static int read_line(FILE *stream, char **line)
{
    if (stream == NULL || line == NULL) {
        return -1;
    }

    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        size_t required = length + 2;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2;
            }

            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        *line = NULL;
        return 0;
    }

    if (buffer == NULL) {
        buffer = malloc(1);

        if (buffer == NULL) {
            return -1;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    int read_result = read_line(stdin, &input);

    if (read_result < 0) {
        return EXIT_FAILURE;
    }

    if (read_result == 0) {
        return EXIT_SUCCESS;
    }

    char *result = remove_duplicate_words(input);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}