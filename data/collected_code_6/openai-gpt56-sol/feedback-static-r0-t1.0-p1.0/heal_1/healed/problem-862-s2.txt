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
        start == NULL || length == 0) {
        return -1;
    }

    char *word = duplicate_lowercase_word(start, length);
    if (word == NULL) {
        return -1;
    }

    for (size_t i = 0; i < *count; ++i) {
        if (strcmp((*words)[i].word, word) == 0) {
            if ((*words)[i].count == SIZE_MAX) {
                free(word);
                return -1;
            }

            ++(*words)[i].count;
            free(word);
            return 0;
        }
    }

    if (*count == *capacity) {
        size_t new_capacity;

        if (*capacity == 0) {
            new_capacity = 16;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                free(word);
                return -1;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(**words)) {
            free(word);
            return -1;
        }

        WordCount *new_words =
            realloc(*words, new_capacity * sizeof(**words));
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
        while (*cursor != '\0' &&
               !isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        const char *start = cursor;

        while (*cursor != '\0' &&
               isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        size_t length = (size_t)(cursor - start);
        if (length != 0 &&
            add_word(&words, &count, &capacity, start, length) != 0) {
            free_word_counts(words, count);
            return -1;
        }
    }

    if (count > 1) {
        qsort(words, count, sizeof(*words), compare_word_counts);
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

static int append_argument(char *destination, size_t capacity,
                           size_t *used, const char *argument,
                           int append_space)
{
    if (destination == NULL || used == NULL || argument == NULL ||
        *used > capacity) {
        return -1;
    }

    size_t remaining = capacity - *used;
    size_t length = strnlen(argument, remaining);

    if (length == remaining) {
        return -1;
    }

    if (length > remaining - 1) {
        return -1;
    }

    memcpy(destination + *used, argument, length);
    *used += length;

    if (append_space) {
        if (*used >= capacity - 1) {
            return -1;
        }
        destination[(*used)++] = ' ';
    }

    destination[*used] = '\0';
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <n> <text>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long parsed_n = strtoull(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || end == NULL || *end != '\0' ||
        parsed_n > SIZE_MAX) {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    size_t text_length = 0;

    for (int i = 2; i < argc; ++i) {
        if (argv[i] == NULL) {
            fprintf(stderr, "Invalid input text\n");
            return EXIT_FAILURE;
        }

        size_t remaining = SIZE_MAX - text_length;
        size_t argument_length = strnlen(argv[i], remaining);

        if (argument_length == remaining) {
            fprintf(stderr, "Input text is too large\n");
            return EXIT_FAILURE;
        }

        text_length += argument_length;

        if (i + 1 < argc) {
            if (text_length == SIZE_MAX) {
                fprintf(stderr, "Input text is too large\n");
                return EXIT_FAILURE;
            }
            ++text_length;
        }
    }

    if (text_length == SIZE_MAX) {
        fprintf(stderr, "Input text is too large\n");
        return EXIT_FAILURE;
    }

    size_t capacity = text_length + 1;
    char *text = malloc(capacity);
    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    text[0] = '\0';
    size_t used = 0;

    for (int i = 2; i < argc; ++i) {
        if (append_argument(text, capacity, &used, argv[i],
                            i + 1 < argc) != 0) {
            fprintf(stderr, "Unable to copy input text\n");
            free(text);
            return EXIT_FAILURE;
        }
    }

    WordCount *results = NULL;
    size_t result_count = 0;

    if (find_most_common_words(text, (size_t)parsed_n,
                               &results, &result_count) != 0) {
        fprintf(stderr, "Unable to process input\n");
        free(text);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; ++i) {
        if (printf("%s: %zu\n", results[i].word,
                   results[i].count) < 0) {
            free_word_counts(results, result_count);
            free(text);
            return EXIT_FAILURE;
        }
    }

    free_word_counts(results, result_count);
    free(text);
    return EXIT_SUCCESS;
}