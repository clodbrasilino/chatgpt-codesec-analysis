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
                                 size_t length)
{
    if (set == NULL || (word == NULL && length != 0)) {
        return 0;
    }

    for (size_t i = 0; i < set->size; ++i) {
        if (set->items[i].length == length &&
            (length == 0 ||
             memcmp(set->items[i].data, word, length) == 0)) {
            return 1;
        }
    }

    return 0;
}

static int string_set_reserve(StringSet *set, size_t minimum_capacity)
{
    if (set == NULL) {
        return -1;
    }

    if (minimum_capacity <= set->capacity) {
        return 0;
    }

    if (minimum_capacity > SIZE_MAX / sizeof(*set->items)) {
        return -1;
    }

    size_t new_capacity = set->capacity == 0 ? 8 : set->capacity;

    while (new_capacity < minimum_capacity) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = minimum_capacity;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*set->items)) {
        return -1;
    }

    StringEntry *new_items =
        realloc(set->items, new_capacity * sizeof(*set->items));

    if (new_items == NULL) {
        return -1;
    }

    set->items = new_items;
    set->capacity = new_capacity;
    return 0;
}

static int string_set_add_n(StringSet *set,
                            const char *word,
                            size_t length)
{
    if (set == NULL ||
        (word == NULL && length != 0) ||
        length == SIZE_MAX ||
        set->size == SIZE_MAX) {
        return -1;
    }

    if (string_set_reserve(set, set->size + 1) != 0) {
        return -1;
    }

    size_t allocation_size = length + 1;
    char *copy = malloc(allocation_size);

    if (copy == NULL) {
        return -1;
    }

    if (length > 0) {
        if (word == NULL || length > allocation_size - 1) {
            free(copy);
            return -1;
        }

        memcpy(copy, word, length);
    }

    copy[length] = '\0';
    set->items[set->size].data = copy;
    set->items[set->size].length = length;
    ++set->size;

    return 0;
}

static char *remove_duplicate_words_n(const char *input, size_t input_length)
{
    if ((input == NULL && input_length != 0) || input_length == SIZE_MAX) {
        return NULL;
    }

    size_t result_capacity = input_length + 1;
    char *result = malloc(result_capacity);

    if (result == NULL) {
        return NULL;
    }

    StringSet seen = {NULL, 0, 0};
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

        if (string_set_contains_n(&seen, input + start, word_length)) {
            continue;
        }

        if (string_set_add_n(&seen, input + start, word_length) != 0) {
            string_set_destroy(&seen);
            free(result);
            return NULL;
        }

        size_t separator_length = first_word ? 0U : 1U;
        size_t available = result_capacity - output_index;

        if (separator_length > available) {
            string_set_destroy(&seen);
            free(result);
            return NULL;
        }

        available -= separator_length;

        if (available == 0 || word_length > available - 1) {
            string_set_destroy(&seen);
            free(result);
            return NULL;
        }

        if (separator_length != 0) {
            result[output_index++] = ' ';
        }

        if (word_length > 0) {
            size_t remaining = result_capacity - output_index;

            if (word_length >= remaining) {
                string_set_destroy(&seen);
                free(result);
                return NULL;
            }

            memcpy(result + output_index, input + start, word_length);
            output_index += word_length;
        }

        first_word = 0;
    }

    result[output_index] = '\0';
    string_set_destroy(&seen);
    return result;
}

static int append_character(char **buffer,
                            size_t *length,
                            size_t *capacity,
                            unsigned char value)
{
    if (buffer == NULL || length == NULL || capacity == NULL) {
        return -1;
    }

    if (*length > *capacity || (*buffer == NULL && *capacity != 0)) {
        return -1;
    }

    if (*length == SIZE_MAX) {
        return -1;
    }

    if (*length == *capacity) {
        size_t required = *length + 1;
        size_t new_capacity = *capacity == 0 ? 128 : *capacity;

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

        char *new_buffer = realloc(*buffer, new_capacity);

        if (new_buffer == NULL) {
            return -1;
        }

        *buffer = new_buffer;
        *capacity = new_capacity;
    }

    (*buffer)[*length] = (char)value;
    ++*length;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    char *local_buffer = NULL;
    size_t local_length = 0;
    size_t capacity = 0;

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(local_buffer);
                return -1;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(local_buffer);
                    return -1;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(local_buffer);
                return -1;
            }

            break;
        }

        if (append_character(&local_buffer,
                             &local_length,
                             &capacity,
                             (unsigned char)ch) != 0) {
            free(local_buffer);
            return -1;
        }
    }

    *buffer = local_buffer;
    *length = local_length;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;

    if (read_line(stdin, &input, &length) != 0) {
        fputs("Failed to read input or allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    static const char empty_input[] = "";
    const char *source = input != NULL ? input : empty_input;
    char *result = remove_duplicate_words_n(source, length);

    free(input);

    if (result == NULL) {
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    int status = EXIT_SUCCESS;

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free(result);
    return status;
}