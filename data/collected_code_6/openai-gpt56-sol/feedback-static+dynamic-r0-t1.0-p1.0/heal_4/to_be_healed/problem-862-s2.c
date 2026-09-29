#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    size_t count;
} WordCount;

static void free_word_counts(WordCount *words, size_t count)
{
    if (words == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(words[i].word);
    }

    free(words);
}

static char *duplicate_lowercase_word(const char *start, size_t length)
{
    if (start == NULL || length == SIZE_MAX) {
        return NULL;
    }

    char *word = malloc(length + 1);
    if (word == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        word[i] = (char)tolower((unsigned char)start[i]);
    }

    word[length] = '\0';
    return word;
}

static int add_word(WordCount **words, size_t *count, size_t *capacity,
                    const char *start, size_t length)
{
    if (words == NULL || count == NULL || capacity == NULL ||
        start == NULL || *count > *capacity) {
        return -1;
    }

    char *word = duplicate_lowercase_word(start, length);
    if (word == NULL) {
        return -1;
    }

    for (size_t i = 0; i < *count; ++i) {
        if (strcmp((*words)[i].word, word) == 0) {
            free(word);

            if ((*words)[i].count == SIZE_MAX) {
                return -1;
            }

            ++(*words)[i].count;
            return 0;
        }
    }

    if (*count == *capacity) {
        size_t new_capacity = (*capacity == 0) ? 16 : *capacity;

        if (*capacity != 0) {
            if (*capacity > SIZE_MAX / 2) {
                free(word);
                return -1;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof **words) {
            free(word);
            return -1;
        }

        WordCount *new_words =
            realloc(*words, new_capacity * sizeof **words);
        if (new_words == NULL) {
            free(word);
            return -1;
        }

        *words = new_words;
        *capacity = new_capacity;
    }

    (*words)[*count].word = word;
    (*words)[*count].count = 1;
    ++*count;

    return 0;
}

static int compare_word_counts(const void *left, const void *right)
{
    const WordCount *a = left;
    const WordCount *b = right;

    if (a->count < b->count) {
        return 1;
    }

    if (a->count > b->count) {
        return -1;
    }

    return strcmp(a->word, b->word);
}

static int find_most_common_words(const char *text, size_t n,
                                  WordCount **result, size_t *result_count)
{
    if (text == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    WordCount *words = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *cursor = text;

    while (*cursor != '\0') {
        while (*cursor != '\0' && !isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        const char *start = cursor;

        while (*cursor != '\0' && isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        size_t length = (size_t)(cursor - start);

        if (length > 0 &&
            add_word(&words, &count, &capacity, start, length) != 0) {
            free_word_counts(words, count);
            return -1;
        }
    }

    if (count > 1) {
        qsort(words, count, sizeof *words, compare_word_counts);
    }

    if (n < count) {
        for (size_t i = n; i < count; ++i) {
            free(words[i].word);
        }
        count = n;
    }

    if (count == 0) {
        free(words);
        words = NULL;
    }

    *result = words;
    *result_count = count;
    return 0;
}

static size_t bounded_string_length(const char *string, size_t limit)
{
    if (string == NULL) {
        return limit;
    }

    const void *terminator = memchr(string, '\0', limit);
    if (terminator == NULL) {
        return limit;
    }

    return (size_t)((const char *)terminator - string);
}

static int append_argument(char **destination, size_t *remaining,
                           const char *argument, size_t argument_length,
                           int add_space)
{
    if (destination == NULL || *destination == NULL ||
        remaining == NULL || argument == NULL) {
        return -1;
    }

    if (argument_length > *remaining) {
        return -1;
    }

    if (argument_length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(*destination, argument, argument_length);
        *destination += argument_length;
        *remaining -= argument_length;
    }

    if (add_space) {
        if (*remaining == 0) {
            return -1;
        }

        **destination = ' ';
        ++*destination;
        --*remaining;
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 3 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <n> <text>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "wordcount");
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long parsed_n = strtoull(argv[1], &end, 10);

    if (errno != 0 || end == NULL || end == argv[1] || *end != '\0' ||
        parsed_n > SIZE_MAX) {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    size_t argument_count = (size_t)(argc - 2);

    if (argument_count > SIZE_MAX / sizeof(size_t)) {
        fprintf(stderr, "Input text is too large\n");
        return EXIT_FAILURE;
    }

    size_t *argument_lengths =
        malloc(argument_count * sizeof *argument_lengths);
    if (argument_lengths == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    size_t text_length = 0;

    for (int i = 2; i < argc; ++i) {
        if (argv[i] == NULL) {
            fprintf(stderr, "Invalid input text\n");
            free(argument_lengths);
            return EXIT_FAILURE;
        }

        size_t available = SIZE_MAX - text_length;
        size_t separator_length = (i + 1 < argc) ? 1U : 0U;

        if (available < separator_length) {
            fprintf(stderr, "Input text is too large\n");
            free(argument_lengths);
            return EXIT_FAILURE;
        }

        size_t maximum_argument_length = available - separator_length;
        size_t scan_limit = maximum_argument_length;

        if (scan_limit < SIZE_MAX) {
            ++scan_limit;
        }

        size_t argument_length =
            bounded_string_length(argv[i], scan_limit);

        if (argument_length == scan_limit) {
            fprintf(stderr, "Input text is too large or invalid\n");
            free(argument_lengths);
            return EXIT_FAILURE;
        }

        argument_lengths[(size_t)(i - 2)] = argument_length;
        text_length += argument_length + separator_length;
    }

    if (text_length == SIZE_MAX) {
        fprintf(stderr, "Input text is too large\n");
        free(argument_lengths);
        return EXIT_FAILURE;
    }

    char *text = malloc(text_length + 1);
    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(argument_lengths);
        return EXIT_FAILURE;
    }

    char *destination = text;
    size_t remaining = text_length;

    for (int i = 2; i < argc; ++i) {
        size_t argument_length = argument_lengths[(size_t)(i - 2)];

        if (append_argument(&destination, &remaining, argv[i],
                            argument_length, i + 1 < argc) != 0) {
            fprintf(stderr, "Unable to construct input text\n");
            free(text);
            free(argument_lengths);
            return EXIT_FAILURE;
        }
    }

    free(argument_lengths);

    if (remaining != 0) {
        free(text);
        return EXIT_FAILURE;
    }

    *destination = '\0';

    WordCount *results = NULL;
    size_t result_count = 0;

    if (find_most_common_words(text, (size_t)parsed_n,
                               &results, &result_count) != 0) {
        fprintf(stderr, "Unable to process input\n");
        free(text);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; ++i) {
        if (printf("%s: %zu\n", results[i].word, results[i].count) < 0) {
            free_word_counts(results, result_count);
            free(text);
            return EXIT_FAILURE;
        }
    }

    free_word_counts(results, result_count);
    free(text);
    return EXIT_SUCCESS;
}