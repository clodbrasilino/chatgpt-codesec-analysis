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

static int string_set_contains(const StringSet *set,
                               const char *word,
                               size_t word_length)
{
    if (set == NULL || word == NULL) {
        return 0;
    }

    for (size_t i = 0; i < set->size; ++i) {
        size_t item_length = strlen(set->items[i]);

        if (item_length == word_length &&
            memcmp(set->items[i], word, word_length) == 0) {
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

        char **new_items =
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

    if (word_length != 0) {
        memmove(copy, word, word_length);
    }
    copy[word_length] = '\0';

    set->items[set->size++] = copy;
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

    StringSet seen = { NULL, 0, 0 };
    size_t input_index = 0;
    size_t output_index = 0;
    int first_word = 1;

    while (input_index < input_length) {
        while (input_index < input_length &&
               isspace((unsigned char)input[input_index])) {
            ++input_index;
        }

        if (input_index == input_length) {
            break;
        }

        size_t start = input_index;

        while (input_index < input_length &&
               !isspace((unsigned char)input[input_index])) {
            ++input_index;
        }

        size_t word_length = input_index - start;

        if (!string_set_contains(&seen, input + start, word_length)) {
            if (string_set_add(&seen, input + start, word_length) != 0) {
                string_set_destroy(&seen);
                free(result);
                return NULL;
            }

            if (!first_word) {
                if (output_index >= input_length) {
                    string_set_destroy(&seen);
                    free(result);
                    return NULL;
                }
                result[output_index++] = ' ';
            }

            if (word_length > input_length - output_index) {
                string_set_destroy(&seen);
                free(result);
                return NULL;
            }

            if (word_length != 0) {
                memmove(result + output_index, input + start, word_length);
            }

            output_index += word_length;
            first_word = 0;
        }
    }

    result[output_index] = '\0';
    string_set_destroy(&seen);
    return result;
}

int main(void)
{
    enum { INPUT_CAPACITY = 4096 };
    char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        fprintf(stderr, "Failed to allocate input buffer.\n");
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            free(input);
            return EXIT_FAILURE;
        }

        free(input);
        return EXIT_SUCCESS;
    }

    size_t input_length = strnlen(input, INPUT_CAPACITY);

    if (input_length == INPUT_CAPACITY) {
        fprintf(stderr, "Invalid input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *line_end = memchr(input, '\n', input_length);

    if (line_end == NULL && !feof(stdin)) {
        fprintf(stderr, "Input is too long.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (line_end != NULL) {
        input_length = (size_t)(line_end - input);
        if (input_length > 0 && input[input_length - 1] == '\r') {
            --input_length;
        }
    } else if (input_length > 0 && input[input_length - 1] == '\r') {
        --input_length;
    }

    char *result = remove_duplicate_words(input, input_length);
    free(input);

    if (result == NULL) {
        fprintf(stderr, "Failed to process input.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}