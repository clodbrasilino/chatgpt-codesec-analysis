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
    size_t i;

    if (collection == NULL) {
        return;
    }

    for (i = 0; i < collection->count; ++i) {
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
    size_t i;

    if (collection == NULL || (word == NULL && length != 0)) {
        return 0;
    }

    for (i = 0; i < collection->count; ++i) {
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
    size_t new_capacity;
    StringItem *new_items;

    if (collection == NULL) {
        return -1;
    }

    if (collection->count < collection->capacity) {
        return 0;
    }

    if (collection->capacity == 0) {
        new_capacity = 8;
    } else {
        if (collection->capacity > SIZE_MAX / 2) {
            return -1;
        }

        new_capacity = collection->capacity * 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_items)) {
        return -1;
    }

    new_items = realloc(collection->items,
                        new_capacity * sizeof(*new_items));
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
    char *copy;

    if (collection == NULL || (word == NULL && length != 0) ||
        length == SIZE_MAX) {
        return -1;
    }

    if (collection_reserve(collection) != 0) {
        return -1;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return -1;
    }

    if (length != 0) {
        memmove(copy, word, length);
    }
    copy[length] = '\0';

    collection->items[collection->count].data = copy;
    collection->items[collection->count].length = length;
    ++collection->count;

    return 0;
}

static char *remove_duplicate_words_n(const char *input, size_t input_length)
{
    StringCollection words = {NULL, 0, 0};
    size_t input_pos = 0;
    size_t output_pos = 0;
    char *result;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return NULL;
    }

    while (input_pos < input_length) {
        size_t start;
        size_t word_length;
        size_t separator_length;
        size_t available;

        while (input_pos < input_length &&
               isspace((unsigned char)input[input_pos]) != 0) {
            ++input_pos;
        }

        if (input_pos == input_length) {
            break;
        }

        start = input_pos;

        while (input_pos < input_length &&
               isspace((unsigned char)input[input_pos]) == 0) {
            ++input_pos;
        }

        word_length = input_pos - start;

        if (collection_contains(&words, input + start, word_length)) {
            continue;
        }

        separator_length = output_pos == 0 ? 0 : 1;

        if (output_pos > input_length) {
            collection_destroy(&words);
            free(result);
            return NULL;
        }

        available = input_length - output_pos;

        if (separator_length > available ||
            word_length > available - separator_length) {
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
            memmove(result + output_pos, input + start, word_length);
            output_pos += word_length;
        }
    }

    result[output_pos] = '\0';
    collection_destroy(&words);

    {
        char *resized = realloc(result, output_pos + 1);
        return resized != NULL ? resized : result;
    }
}

char *remove_duplicate_words(const char *input)
{
    const char *end;
    size_t length;

    if (input == NULL) {
        return NULL;
    }

    end = strchr(input, '\0');
    length = (size_t)(end - input);

    return remove_duplicate_words_n(input, length);
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || *buffer == NULL ||
        *capacity == 0 || *capacity > SIZE_MAX / 2) {
        return -1;
    }

    new_capacity = *capacity * 2;
    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static char *read_line(FILE *stream, size_t *length_out)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL || length_out == NULL) {
        return NULL;
    }

    *length_out = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) != 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        if (length >= capacity - 1) {
            if (grow_buffer(&buffer, &capacity) != 0) {
                free(buffer);
                return NULL;
            }
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length != 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *length_out = length;

    {
        char *resized = realloc(buffer, length + 1);
        return resized != NULL ? resized : buffer;
    }
}

int main(void)
{
    size_t input_length;
    char *input;
    char *result;
    int status;

    input = read_line(stdin, &input_length);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    result = remove_duplicate_words_n(input, input_length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    status = puts(result);
    free(result);

    return status == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}