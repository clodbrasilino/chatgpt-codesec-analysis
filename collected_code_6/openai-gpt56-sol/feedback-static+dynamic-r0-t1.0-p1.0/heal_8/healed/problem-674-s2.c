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
    size_t count;
    size_t capacity;
} StringCollection;

static void collection_destroy(StringCollection *collection)
{
    if (collection == NULL) {
        return;
    }

    for (size_t i = 0; i < collection->count; ++i) {
        free(collection->items[i].data);
    }

    free(collection->items);
    collection->items = NULL;
    collection->count = 0;
    collection->capacity = 0;
}

static int collection_contains(const StringCollection *collection,
                               const char *word,
                               size_t length)
{
    if (collection == NULL || (word == NULL && length != 0)) {
        return 0;
    }

    for (size_t i = 0; i < collection->count; ++i) {
        const StringItem *item = &collection->items[i];

        if (item->length == length &&
            (length == 0 || memcmp(item->data, word, length) == 0)) {
            return 1;
        }
    }

    return 0;
}

static int collection_reserve(StringCollection *collection)
{
    if (collection == NULL) {
        return -1;
    }

    if (collection->count < collection->capacity) {
        return 0;
    }

    size_t new_capacity;

    if (collection->capacity == 0) {
        new_capacity = 8;
    } else {
        if (collection->capacity > SIZE_MAX / 2) {
            return -1;
        }
        new_capacity = collection->capacity * 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*collection->items)) {
        return -1;
    }

    StringItem *new_items =
        realloc(collection->items, new_capacity * sizeof(*new_items));

    if (new_items == NULL) {
        return -1;
    }

    collection->items = new_items;
    collection->capacity = new_capacity;
    return 0;
}

static int collection_add(StringCollection *collection,
                          const char *word,
                          size_t length)
{
    if (collection == NULL || (word == NULL && length != 0) ||
        length == SIZE_MAX) {
        return -1;
    }

    if (collection_reserve(collection) != 0) {
        return -1;
    }

    char *copy = malloc(length + 1);
    if (copy == NULL) {
        return -1;
    }

    if (length != 0) {
        memcpy(copy, word, length);
    }
    copy[length] = '\0';

    collection->items[collection->count].data = copy;
    collection->items[collection->count].length = length;
    ++collection->count;

    return 0;
}

static char *remove_duplicate_words_n(const char *input, size_t input_length)
{
    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(input_length + 1);
    if (result == NULL) {
        return NULL;
    }

    StringCollection words = {NULL, 0, 0};
    size_t input_pos = 0;
    size_t output_pos = 0;

    while (input_pos < input_length) {
        while (input_pos < input_length &&
               isspace((unsigned char)input[input_pos])) {
            ++input_pos;
        }

        if (input_pos == input_length) {
            break;
        }

        size_t start = input_pos;

        while (input_pos < input_length &&
               !isspace((unsigned char)input[input_pos])) {
            ++input_pos;
        }

        size_t word_length = input_pos - start;

        if (collection_contains(&words, input + start, word_length)) {
            continue;
        }

        size_t separator_length = output_pos == 0 ? 0 : 1;

        if (word_length > input_length - output_pos ||
            separator_length >
                input_length - output_pos - word_length) {
            collection_destroy(&words);
            free(result);
            return NULL;
        }

        if (collection_add(&words, input + start, word_length) != 0) {
            collection_destroy(&words);
            free(result);
            return NULL;
        }

        if (separator_length != 0) {
            result[output_pos++] = ' ';
        }

        if (word_length != 0) {
            memcpy(result + output_pos, input + start, word_length);
            output_pos += word_length;
        }
    }

    result[output_pos] = '\0';
    collection_destroy(&words);

    char *resized = realloc(result, output_pos + 1);
    return resized != NULL ? resized : result;
}

char *remove_duplicate_words(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    return remove_duplicate_words_n(input, strlen(input));
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    if (buffer == NULL || capacity == NULL || *buffer == NULL ||
        *capacity == 0 || *capacity > SIZE_MAX / 2) {
        return -1;
    }

    size_t new_capacity = *capacity * 2;
    char *new_buffer = realloc(*buffer, new_capacity);

    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static char *read_line(FILE *stream, size_t *length_out)
{
    if (stream == NULL || length_out == NULL) {
        return NULL;
    }

    *length_out = 0;

    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            if (grow_buffer(&buffer, &capacity) != 0) {
                free(buffer);
                return NULL;
            }
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *length_out = length;

    char *resized = realloc(buffer, length + 1);
    return resized != NULL ? resized : buffer;
}

int main(void)
{
    size_t input_length;
    char *input = read_line(stdin, &input_length);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    char *result = remove_duplicate_words_n(input, input_length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    int status = puts(result);
    free(result);

    return status == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}