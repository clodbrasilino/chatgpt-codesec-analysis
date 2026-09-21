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

    if (string_set_contains_n(set, word, length)) {
        return 0;
    }

    if (string_set_reserve(set, set->size + 1) != 0) {
        return -1;
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

    char *result = malloc(input_length + 1);
    if (result == NULL) {
        return NULL;
    }

    StringSet seen = {0};
    size_t input_index = 0;
    size_t output_index = 0;
    int first_word = 1;

    while (input_index < input_length) {
        while (input_index < input_length &&
               isspace((unsigned char)input[input_index]) != 0) {
            ++input_index;
        }

        if (input_index == input_length) {
            break;
        }

        size_t start = input_index;

        while (input_index < input_length &&
               isspace((unsigned char)input[input_index]) == 0) {
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

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + output_index, input + start, word_length);
        output_index += word_length;
        first_word = 0;
    }

    result[output_index] = '\0';
    string_set_destroy(&seen);
    return result;
}

static int grow_buffer(char **buffer,
                       size_t *capacity,
                       size_t required_capacity)
{
    if (buffer == NULL || capacity == NULL ||
        required_capacity == 0 ||
        (*buffer == NULL && *capacity != 0) ||
        (*buffer != NULL && *capacity == 0)) {
        return -1;
    }

    if (required_capacity <= *capacity) {
        return 0;
    }

    size_t new_capacity = *capacity == 0 ? 128 : *capacity;

    while (new_capacity < required_capacity) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required_capacity;
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

static int append_character(char **buffer,
                            size_t *length,
                            size_t *capacity,
                            unsigned char value)
{
    if (buffer == NULL || length == NULL || capacity == NULL ||
        *length > *capacity ||
        (*buffer == NULL && *capacity != 0) ||
        (*buffer != NULL && *capacity == 0) ||
        *length == SIZE_MAX) {
        return -1;
    }

    size_t required_capacity = *length + 1;

    if (grow_buffer(buffer, capacity, required_capacity) != 0) {
        return -1;
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
    size_t local_capacity = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char block[4096];
    int finished = 0;

    while (!finished) {
        size_t count = fread(block, 1, sizeof(block), stream);

        if (count == 0) {
            if (ferror(stream)) {
                free(local_buffer);
                return -1;
            }
            break;
        }

        size_t consumed = 0;

        while (consumed < count) {
            unsigned char ch = block[consumed++];

            if (ch == '\n') {
                finished = 1;
                break;
            }

            if (ch == '\r') {
                if (consumed < count) {
                    if (block[consumed] == '\n') {
                        ++consumed;
                    }
                } else {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
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
                }

                finished = 1;
                break;
            }

            if (append_character(&local_buffer,
                                 &local_length,
                                 &local_capacity,
                                 ch) != 0) {
                free(local_buffer);
                return -1;
            }
        }

        if (consumed < count) {
            for (size_t i = count; i > consumed; --i) {
                if (ungetc((int)block[i - 1], stream) == EOF) {
                    free(local_buffer);
                    return -1;
                }
            }
        }
    }

    *buffer = local_buffer;
    *length = local_length;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t input_length = 0;

    if (read_line(stdin, &input, &input_length) != 0) {
        fputs("Failed to read input or allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    static const char empty_input[] = "";
    const char *source = input != NULL ? input : empty_input;

    char *result = remove_duplicate_words_n(source, input_length);
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