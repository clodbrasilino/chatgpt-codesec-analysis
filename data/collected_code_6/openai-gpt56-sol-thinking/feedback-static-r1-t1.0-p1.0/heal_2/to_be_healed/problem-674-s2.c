#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *word;
    size_t length;
} WordEntry;

typedef struct {
    WordEntry *entries;
    size_t capacity;
} WordSet;

static size_t hash_word(const char *word, size_t length)
{
    size_t hash = 5381U;
    size_t i;

    for (i = 0U; i < length; ++i) {
        hash = (hash * 33U) ^ (unsigned char)word[i];
    }

    return hash;
}

static bool words_equal(const char *left, const char *right, size_t length)
{
    size_t i;

    for (i = 0U; i < length; ++i) {
        if (left[i] != right[i]) {
            return false;
        }
    }

    return true;
}

static bool word_set_initialize(WordSet *set, size_t expected_count)
{
    size_t capacity = 8U;
    size_t target;

    if (set == NULL) {
        return false;
    }

    set->entries = NULL;
    set->capacity = 0U;

    if (expected_count == 0U) {
        return true;
    }

    if (expected_count > SIZE_MAX / 2U) {
        return false;
    }

    target = expected_count * 2U;

    while (capacity < target) {
        if (capacity > SIZE_MAX / 2U) {
            return false;
        }

        capacity *= 2U;
    }

    if (capacity > SIZE_MAX / sizeof(*set->entries)) {
        return false;
    }

    set->entries = calloc(capacity, sizeof(*set->entries));
    if (set->entries == NULL) {
        return false;
    }

    set->capacity = capacity;
    return true;
}

static void word_set_destroy(WordSet *set)
{
    if (set != NULL) {
        free(set->entries);
        set->entries = NULL;
        set->capacity = 0U;
    }
}

static int word_set_insert(WordSet *set, const char *word, size_t length)
{
    size_t index;
    size_t probes;

    if (set == NULL || set->entries == NULL || set->capacity == 0U ||
        word == NULL || length == 0U) {
        return -1;
    }

    index = hash_word(word, length) & (set->capacity - 1U);

    for (probes = 0U; probes < set->capacity; ++probes) {
        WordEntry *entry = &set->entries[index];

        if (entry->word == NULL) {
            entry->word = word;
            entry->length = length;
            return 1;
        }

        if (entry->length == length &&
            words_equal(entry->word, word, length)) {
            return 0;
        }

        index = (index + 1U) & (set->capacity - 1U);
    }

    return -1;
}

static bool remove_duplicate_words(const char *input, size_t input_length,
                                   char **result, size_t *result_length)
{
    WordSet words;
    char *output;
    size_t word_count = 0U;
    size_t input_position = 0U;
    size_t output_position = 0U;

    if (input == NULL || result == NULL || result_length == NULL) {
        return false;
    }

    *result = NULL;
    *result_length = 0U;

    while (input_position < input_length) {
        while (input_position < input_length &&
               isspace((unsigned char)input[input_position]) != 0) {
            ++input_position;
        }

        if (input_position == input_length) {
            break;
        }

        if (word_count == SIZE_MAX) {
            return false;
        }

        ++word_count;

        while (input_position < input_length &&
               isspace((unsigned char)input[input_position]) == 0) {
            ++input_position;
        }
    }

    if (!word_set_initialize(&words, word_count)) {
        return false;
    }

    if (input_length == SIZE_MAX) {
        word_set_destroy(&words);
        return false;
    }

    output = malloc(input_length + 1U);
    if (output == NULL) {
        word_set_destroy(&words);
        return false;
    }

    input_position = 0U;

    while (input_position < input_length) {
        size_t word_start;
        size_t word_length;
        /* Possible weaknesses found:
         *  The scope of the variable 'i' can be reduced. [variableScope]
         */
        size_t i;
        int insertion_result;

        while (input_position < input_length &&
               isspace((unsigned char)input[input_position]) != 0) {
            ++input_position;
        }

        if (input_position == input_length) {
            break;
        }

        word_start = input_position;

        while (input_position < input_length &&
               isspace((unsigned char)input[input_position]) == 0) {
            ++input_position;
        }

        word_length = input_position - word_start;
        insertion_result = word_set_insert(
            &words, input + word_start, word_length
        );

        if (insertion_result < 0) {
            free(output);
            word_set_destroy(&words);
            return false;
        }

        if (insertion_result > 0) {
            if (output_position != 0U) {
                if (output_position >= input_length) {
                    free(output);
                    word_set_destroy(&words);
                    return false;
                }

                output[output_position++] = ' ';
            }

            if (word_length > input_length - output_position) {
                free(output);
                word_set_destroy(&words);
                return false;
            }

            for (i = 0U; i < word_length; ++i) {
                output[output_position + i] = input[word_start + i];
            }

            output_position += word_length;
        }
    }

    output[output_position] = '\0';
    word_set_destroy(&words);

    *result = output;
    *result_length = output_position;
    return true;
}

static bool read_standard_input(char **result, size_t *result_length)
{
    char *buffer;
    size_t capacity = 4096U;
    size_t length = 0U;

    if (result == NULL || result_length == NULL) {
        return false;
    }

    *result = NULL;
    *result_length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        size_t available;
        size_t bytes_read;

        if (length == capacity - 1U) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        available = capacity - length - 1U;
        bytes_read = fread(buffer + length, 1U, available, stdin);
        length += bytes_read;

        if (bytes_read < available) {
            if (ferror(stdin) != 0) {
                free(buffer);
                return false;
            }

            if (feof(stdin) != 0) {
                break;
            }

            if (bytes_read == 0U) {
                free(buffer);
                return false;
            }
        }
    }

    if (memchr(buffer, '\0', length) != NULL) {
        free(buffer);
        return false;
    }

    buffer[length] = '\0';
    *result = buffer;
    *result_length = length;
    return true;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t input_length = 0U;
    size_t output_length = 0U;
    int exit_status = EXIT_SUCCESS;

    if (!read_standard_input(&input, &input_length)) {
        return EXIT_FAILURE;
    }

    if (!remove_duplicate_words(input, input_length,
                                &output, &output_length)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (fwrite(output, 1U, output_length, stdout) != output_length ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        exit_status = EXIT_FAILURE;
    }

    free(output);
    free(input);
    return exit_status;
}