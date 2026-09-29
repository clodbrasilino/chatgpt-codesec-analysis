#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t length;
} StringEntry;

typedef struct {
    StringEntry *items;
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

static int string_set_contains_n(const StringSet *set,
                                 const char *word,
                                 size_t word_length)
{
    if (set == NULL || word == NULL) {
        return 0;
    }

    for (size_t i = 0; i < set->size; ++i) {
        if (set->items[i].length == word_length &&
            (word_length == 0 ||
             memcmp(set->items[i].data, word, word_length) == 0)) {
            return 1;
        }
    }

    return 0;
}

static int string_set_reserve(StringSet *set, size_t required)
{
    if (set == NULL) {
        return -1;
    }

    if (required <= set->capacity) {
        return 0;
    }

    if (required > SIZE_MAX / sizeof(*set->items)) {
        return -1;
    }

    size_t new_capacity = set->capacity == 0 ? 8 : set->capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*set->items)) {
        return -1;
    }

    StringEntry *new_items =
        realloc(set->items, new_capacity * sizeof(*new_items));

    if (new_items == NULL) {
        return -1;
    }

    set->items = new_items;
    set->capacity = new_capacity;
    return 0;
}

static int string_set_add_n(StringSet *set,
                            const char *word,
                            size_t word_length)
{
    if (set == NULL || word == NULL || word_length == SIZE_MAX) {
        return -1;
    }

    if (string_set_contains_n(set, word, word_length)) {
        return 0;
    }

    if (set->size == SIZE_MAX ||
        string_set_reserve(set, set->size + 1) != 0) {
        return -1;
    }

    size_t allocation_size = word_length + 1;
    char *copy = malloc(allocation_size);

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

static int buffer_reserve(char **buffer,
                          size_t *capacity,
                          size_t required)
{
    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    size_t new_capacity = *capacity == 0 ? 16 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    char *new_buffer = realloc(*buffer, new_capacity);

    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int append_word_n(char **output,
                         size_t *length,
                         size_t *capacity,
                         const char *word,
                         size_t word_length)
{
    if (output == NULL || length == NULL || capacity == NULL ||
        word == NULL || *length > *capacity) {
        return -1;
    }

    size_t separator_length = *length == 0 ? 0 : 1;

    if (*length > SIZE_MAX - separator_length) {
        return -1;
    }

    size_t new_length = *length + separator_length;

    if (new_length > SIZE_MAX - word_length) {
        return -1;
    }

    new_length += word_length;

    if (new_length == SIZE_MAX) {
        return -1;
    }

    size_t required = new_length + 1;

    if (buffer_reserve(output, capacity, required) != 0 ||
        required > *capacity) {
        return -1;
    }

    size_t position = *length;

    if (separator_length != 0) {
        (*output)[position++] = ' ';
    }

    if (word_length > 0) {
        memcpy(*output + position, word, word_length);
        position += word_length;
    }

    (*output)[position] = '\0';
    *length = position;
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
        while (*cursor != '\0' &&
               isspace((unsigned char)*cursor) != 0) {
            ++cursor;
        }

        const char *start = cursor;

        while (*cursor != '\0' &&
               isspace((unsigned char)*cursor) == 0) {
            ++cursor;
        }

        size_t word_length = (size_t)(cursor - start);

        if (word_length == 0) {
            continue;
        }

        int add_result = string_set_add_n(&words, start, word_length);

        if (add_result < 0) {
            string_set_destroy(&words);
            free(output);
            return NULL;
        }

        if (add_result > 0 &&
            append_word_n(&output,
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

static int read_line(FILE *stream, char **line)
{
    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF || character == '\n') {
            if (character == EOF && ferror(stream)) {
                free(buffer);
                return -1;
            }

            if (character == EOF && length == 0) {
                free(buffer);
                return 0;
            }

            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        size_t required = length + 2;

        if (buffer_reserve(&buffer, &capacity, required) != 0 ||
            required > capacity) {
            free(buffer);
            return -1;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (length == SIZE_MAX ||
        buffer_reserve(&buffer, &capacity, length + 1) != 0 ||
        length >= capacity) {
        free(buffer);
        return -1;
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

    int status = puts(result) == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
    free(result);

    return status;
}