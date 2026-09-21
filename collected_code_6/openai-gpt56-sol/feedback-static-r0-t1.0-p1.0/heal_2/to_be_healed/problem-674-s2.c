#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *text;
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
        free(collection->items[i].text);
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
        if (collection->items[i].length == length &&
            memcmp(collection->items[i].text, word, length) == 0) {
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

        StringItem *new_items =
            realloc(collection->items,
                    new_capacity * sizeof(*collection->items));

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

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, word, length);
    }
    copy[length] = '\0';

    collection->items[collection->count].text = copy;
    collection->items[collection->count].length = length;
    ++collection->count;

    return 0;
}

static char *remove_duplicate_words(const char *input, size_t input_length)
{
    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(input_length + 1);
    if (result == NULL) {
        return NULL;
    }

    StringCollection words = { NULL, 0, 0 };
    size_t input_pos = 0;
    size_t output_pos = 0;
    int first_word = 1;

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

        if (!collection_contains(&words, input + start, word_length)) {
            if (collection_add(&words, input + start, word_length) != 0) {
                collection_destroy(&words);
                free(result);
                return NULL;
            }

            if (!first_word) {
                if (output_pos >= input_length) {
                    collection_destroy(&words);
                    free(result);
                    return NULL;
                }
                result[output_pos++] = ' ';
            }

            if (word_length > input_length - output_pos) {
                collection_destroy(&words);
                free(result);
                return NULL;
            }

            if (word_length != 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + output_pos, input + start, word_length);
            }
            output_pos += word_length;
            first_word = 0;
        }
    }

    result[output_pos] = '\0';
    collection_destroy(&words);

    char *resized = realloc(result, output_pos + 1);
    return resized != NULL ? resized : result;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    size_t capacity = 128;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    size_t used = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (used == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (used + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && used == 0) {
        free(buffer);
        *line = NULL;
        *length = 0;
        return 0;
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t input_length = 0;

    int read_status = read_line(stdin, &input, &input_length);
    if (read_status < 0) {
        return EXIT_FAILURE;
    }

    if (read_status == 0) {
        return EXIT_SUCCESS;
    }

    char *result = remove_duplicate_words(input, input_length);
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