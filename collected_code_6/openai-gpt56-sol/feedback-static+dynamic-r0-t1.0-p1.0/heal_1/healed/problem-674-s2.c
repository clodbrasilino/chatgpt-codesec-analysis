#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} StringCollection;

static void collection_destroy(StringCollection *collection)
{
    if (collection == NULL) {
        return;
    }

    for (size_t i = 0; i < collection->count; ++i) {
        free(collection->items[i]);
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
    if (collection == NULL || word == NULL) {
        return 0;
    }

    for (size_t i = 0; i < collection->count; ++i) {
        const char *item = collection->items[i];

        if (strlen(item) == length && memcmp(item, word, length) == 0) {
            return 1;
        }
    }

    return 0;
}

static int collection_add(StringCollection *collection,
                          const char *word,
                          size_t length)
{
    if (collection == NULL || word == NULL || length == SIZE_MAX) {
        return -1;
    }

    if (collection->count == collection->capacity) {
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

        char **new_items = realloc(
            collection->items,
            new_capacity * sizeof(*collection->items)
        );

        if (new_items == NULL) {
            return -1;
        }

        collection->items = new_items;
        collection->capacity = new_capacity;
    }

    char *copy = malloc(length + 1);
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, word, length);
    copy[length] = '\0';
    collection->items[collection->count++] = copy;

    return 0;
}

char *remove_duplicate_words(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    size_t input_length = strlen(input);
    char *result = malloc(input_length + 1);

    if (result == NULL) {
        return NULL;
    }

    StringCollection words = {NULL, 0, 0};
    size_t input_pos = 0;
    size_t output_pos = 0;

    while (input[input_pos] != '\0') {
        while (input[input_pos] != '\0' &&
               isspace((unsigned char)input[input_pos])) {
            ++input_pos;
        }

        if (input[input_pos] == '\0') {
            break;
        }

        size_t start = input_pos;

        while (input[input_pos] != '\0' &&
               !isspace((unsigned char)input[input_pos])) {
            ++input_pos;
        }

        size_t word_length = input_pos - start;

        if (!collection_contains(&words, input + start, word_length)) {
            if (collection_add(&words, input + start, word_length) != 0) {
                collection_destroy(&words);
                free(result);
                return NULL;
            }

            if (output_pos != 0) {
                result[output_pos++] = ' ';
            }

            memcpy(result + output_pos, input + start, word_length);
            output_pos += word_length;
        }
    }

    result[output_pos] = '\0';
    collection_destroy(&words);

    char *resized = realloc(result, output_pos + 1);
    return resized != NULL ? resized : result;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    int ch;

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (ch == '\r') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                ungetc(next, stream);
            }
            break;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
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