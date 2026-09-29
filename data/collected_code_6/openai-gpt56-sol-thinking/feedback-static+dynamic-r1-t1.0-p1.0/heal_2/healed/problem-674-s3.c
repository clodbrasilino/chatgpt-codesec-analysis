#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const char *data;
    size_t length;
} WordReference;

static int is_word_separator(unsigned char c)
{
    return c == ' ' || c == '\t' || c == '\r' ||
           c == '\n' || c == '\v' || c == '\f';
}

static int get_string_length(const char *string, size_t *length)
{
    size_t result = 0;

    if (string == NULL || length == NULL) {
        return 0;
    }

    while (string[result] != '\0') {
        if (result == SIZE_MAX) {
            return 0;
        }
        ++result;
    }

    *length = result;
    return 1;
}

static int words_equal(const WordReference *word,
                       const char *data,
                       size_t length)
{
    size_t i;

    if (word->length != length) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        if (word->data[i] != data[i]) {
            return 0;
        }
    }

    return 1;
}

static int word_is_seen(const WordReference *seen,
                        size_t count,
                        const char *data,
                        size_t length)
{
    size_t i;

    for (i = 0; i < count; ++i) {
        if (words_equal(&seen[i], data, length)) {
            return 1;
        }
    }

    return 0;
}

static int add_seen_word(WordReference **seen,
                         size_t *count,
                         size_t *capacity,
                         const char *data,
                         size_t length)
{
    if (*count == *capacity) {
        WordReference *new_seen;
        size_t new_capacity;

        if (*capacity == 0) {
            new_capacity = 8;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof *new_seen) {
            return 0;
        }

        new_seen = realloc(*seen, new_capacity * sizeof *new_seen);
        if (new_seen == NULL) {
            return 0;
        }

        *seen = new_seen;
        *capacity = new_capacity;
    }

    (*seen)[*count].data = data;
    (*seen)[*count].length = length;
    ++*count;

    return 1;
}

char *remove_duplicate_words(const char *input)
{
    WordReference *seen = NULL;
    char *output;
    size_t input_length;
    size_t output_length = 0;
    size_t seen_count = 0;
    size_t seen_capacity = 0;
    size_t cursor = 0;

    if (!get_string_length(input, &input_length)) {
        return NULL;
    }

    if (input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    while (cursor < input_length) {
        const char *word;
        size_t word_start;
        size_t word_length;
        size_t i;

        while (cursor < input_length &&
               is_word_separator((unsigned char)input[cursor])) {
            ++cursor;
        }

        if (cursor == input_length) {
            break;
        }

        word_start = cursor;

        while (cursor < input_length &&
               !is_word_separator((unsigned char)input[cursor])) {
            ++cursor;
        }

        word = input + word_start;
        word_length = cursor - word_start;

        if (word_is_seen(seen, seen_count, word, word_length)) {
            continue;
        }

        if (!add_seen_word(&seen, &seen_count, &seen_capacity,
                           word, word_length)) {
            free(seen);
            free(output);
            return NULL;
        }

        if (output_length != 0) {
            if (output_length >= input_length) {
                free(seen);
                free(output);
                return NULL;
            }
            output[output_length++] = ' ';
        }

        if (word_length > input_length - output_length) {
            free(seen);
            free(output);
            return NULL;
        }

        for (i = 0; i < word_length; ++i) {
            output[output_length + i] = word[i];
        }

        output_length += word_length;
    }

    output[output_length] = '\0';
    free(seen);

    return output;
}

int main(int argc, char *const argv[])
{
    char *input;
    char *result;
    size_t total_length = 0;
    size_t position = 0;
    int status = EXIT_SUCCESS;
    int i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (i = 1; i < argc; ++i) {
        size_t argument_length;

        if (!get_string_length(argv[i], &argument_length)) {
            fprintf(stderr, "Invalid input argument\n");
            return EXIT_FAILURE;
        }

        if (i > 1) {
            if (total_length == SIZE_MAX) {
                fprintf(stderr, "Input is too large\n");
                return EXIT_FAILURE;
            }
            ++total_length;
        }

        if (argument_length > SIZE_MAX - total_length) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        total_length += argument_length;
    }

    if (total_length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    input = malloc(total_length + 1);
    if (input == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    for (i = 1; i < argc; ++i) {
        size_t argument_length;
        size_t j;

        if (!get_string_length(argv[i], &argument_length)) {
            free(input);
            fprintf(stderr, "Invalid input argument\n");
            return EXIT_FAILURE;
        }

        if (i > 1) {
            input[position++] = ' ';
        }

        if (argument_length > total_length - position) {
            free(input);
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        for (j = 0; j < argument_length; ++j) {
            input[position + j] = argv[i][j];
        }

        position += argument_length;
    }

    input[position] = '\0';

    result = remove_duplicate_words(input);
    free(input);

    if (result == NULL) {
        fprintf(stderr, "Failed to process the input string\n");
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free(result);
    return status;
}