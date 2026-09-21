#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t length;
} StringItem;

typedef struct {
    StringItem *items;
    size_t size;
    size_t capacity;
} StringSet;

static void string_set_destroy(StringSet *set)
{
    if (set == NULL) {
        return;
    }

    for (size_t i = 0; i < set->size; ++i) {
        free(set->items[i].data);
    }

    free(set->items);
    set->items = NULL;
    set->size = 0;
    set->capacity = 0;
}

static int string_set_contains(const StringSet *set,
                               const char *word,
                               size_t word_length)
{
    if (set == NULL || word == NULL) {
        return 0;
    }

    for (size_t i = 0; i < set->size; ++i) {
        if (set->items[i].length == word_length &&
            memcmp(set->items[i].data, word, word_length) == 0) {
            return 1;
        }
    }

    return 0;
}

static int string_set_add(StringSet *set,
                          const char *word,
                          size_t word_length)
{
    if (set == NULL || word == NULL || word_length == SIZE_MAX) {
        return -1;
    }

    if (string_set_contains(set, word, word_length)) {
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

        StringItem *new_items =
            realloc(set->items, new_capacity * sizeof(*set->items));

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

    if (word_length > 0) {
        memcpy(copy, word, word_length);
    }

    copy[word_length] = '\0';
    set->items[set->size].data = copy;
    set->items[set->size].length = word_length;
    ++set->size;

    return 1;
}

static int append_word(char **output,
                       size_t *length,
                       size_t *capacity,
                       const char *word,
                       size_t word_length)
{
    if (output == NULL || length == NULL || capacity == NULL ||
        word == NULL || *length > *capacity) {
        return -1;
    }

    size_t separator_length = (*length == 0) ? 0 : 1;

    if (separator_length > SIZE_MAX - *length) {
        return -1;
    }

    size_t required = *length + separator_length;

    if (word_length > SIZE_MAX - required) {
        return -1;
    }

    required += word_length;

    if (required == SIZE_MAX) {
        return -1;
    }

    ++required;

    if (required > *capacity) {
        size_t new_capacity = (*capacity == 0) ? 16 : *capacity;

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

    if (word_length > 0) {
        memcpy(*output + *length, word, word_length);
        *length += word_length;
    }

    (*output)[*length] = '\0';
    return 0;
}

char *remove_duplicate_words(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    StringSet words = {NULL, 0, 0};
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

        int add_result = string_set_add(&words, start, word_length);

        if (add_result < 0) {
            string_set_destroy(&words);
            free(output);
            return NULL;
        }

        if (add_result > 0 &&
            append_word(&output,
                        &output_length,
                        &output_capacity,
                        start,
                        word_length) != 0) {
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

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    char *line = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character = EOF;

    for (;;) {
        character = fgetc(stream);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(line);
            return NULL;
        }

        size_t required = length + 2;

        if (required > capacity) {
            size_t new_capacity = (capacity == 0) ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *new_line = realloc(line, new_capacity);

            if (new_line == NULL) {
                free(line);
                return NULL;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)character;
    }

    if (ferror(stream)) {
        free(line);
        return NULL;
    }

    if (character == EOF && length == 0) {
        free(line);
        return NULL;
    }

    if (length > 0 && line[length - 1] == '\r') {
        --length;
    }

    if (line == NULL) {
        line = malloc(1);

        if (line == NULL) {
            return NULL;
        }
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
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