#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    size_t length;
    size_t count;
} WordCount;

typedef struct {
    WordCount *items;
    size_t length;
    size_t capacity;
} WordTable;

static void free_word_table(WordTable *table)
{
    size_t i;

    if (table == NULL) {
        return;
    }

    for (i = 0; i < table->length; ++i) {
        free(table->items[i].word);
    }

    free(table->items);
    table->items = NULL;
    table->length = 0;
    table->capacity = 0;
}

static int reserve_word_table(WordTable *table, size_t required)
{
    WordCount *new_items;
    size_t new_capacity;

    if (table == NULL) {
        return -1;
    }

    if (required <= table->capacity) {
        return 0;
    }

    new_capacity = table->capacity == 0 ? 16 : table->capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_items)) {
        return -1;
    }

    new_items = realloc(table->items, new_capacity * sizeof(*new_items));
    if (new_items == NULL) {
        return -1;
    }

    table->items = new_items;
    table->capacity = new_capacity;
    return 0;
}

static int add_word(WordTable *table, const char *word, size_t length)
{
    char *copy;
    size_t i;

    if (table == NULL || (word == NULL && length != 0)) {
        return -1;
    }

    for (i = 0; i < table->length; ++i) {
        if (table->items[i].length == length &&
            memcmp(table->items[i].word, word, length) == 0) {
            if (table->items[i].count == SIZE_MAX) {
                return -1;
            }

            ++table->items[i].count;
            return 0;
        }
    }

    if (length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return -1;
    }

    if (length != 0) {
        memcpy(copy, word, length);
    }
    copy[length] = '\0';

    if (table->length == SIZE_MAX ||
        reserve_word_table(table, table->length + 1) != 0) {
        free(copy);
        return -1;
    }

    table->items[table->length].word = copy;
    table->items[table->length].length = length;
    table->items[table->length].count = 1;
    ++table->length;

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

static int append_character(char **word, size_t *length, size_t *capacity,
                            char character)
{
    char *new_word;
    size_t new_capacity;

    if (word == NULL || *word == NULL || length == NULL || capacity == NULL) {
        return -1;
    }

    if (*length == SIZE_MAX) {
        return -1;
    }

    if (*length + 1 >= *capacity) {
        if (*capacity > SIZE_MAX / 2) {
            return -1;
        }

        new_capacity = *capacity * 2;
        new_word = realloc(*word, new_capacity);
        if (new_word == NULL) {
            return -1;
        }

        *word = new_word;
        *capacity = new_capacity;
    }

    (*word)[*length] = character;
    ++*length;

    return 0;
}

static int find_most_common_words(const char *text, size_t n,
                                  WordTable *result)
{
    char *word;
    size_t word_length = 0;
    size_t word_capacity = 32;
    const unsigned char *cursor;

    if (text == NULL || result == NULL) {
        return -1;
    }

    result->items = NULL;
    result->length = 0;
    result->capacity = 0;

    word = malloc(word_capacity);
    if (word == NULL) {
        return -1;
    }

    cursor = (const unsigned char *)text;

    for (;;) {
        unsigned char character = *cursor;

        if (isalnum(character) != 0 || character == (unsigned char)'_') {
            if (append_character(&word, &word_length, &word_capacity,
                                 (char)tolower(character)) != 0) {
                free(word);
                free_word_table(result);
                return -1;
            }
        } else if (word_length != 0) {
            word[word_length] = '\0';

            if (add_word(result, word, word_length) != 0) {
                free(word);
                free_word_table(result);
                return -1;
            }

            word_length = 0;
        }

        if (character == '\0') {
            break;
        }

        ++cursor;
    }

    free(word);

    if (result->length > 1) {
        qsort(result->items, result->length, sizeof(*result->items),
              compare_word_counts);
    }

    if (result->length > n) {
        size_t i;

        for (i = n; i < result->length; ++i) {
            free(result->items[i].word);
            result->items[i].word = NULL;
            result->items[i].length = 0;
            result->items[i].count = 0;
        }

        result->length = n;
    }

    return 0;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

int main(int argc, char *argv[])
{
    WordTable result = { NULL, 0, 0 };
    size_t n;
    size_t i;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_size(argv[1], &n) != 0) {
        fputs("Invalid value for n\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_most_common_words(argv[2], n, &result) != 0) {
        fputs("Failed to process text\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result.length; ++i) {
        if (printf("%s: %zu\n", result.items[i].word,
                   result.items[i].count) < 0) {
            free_word_table(&result);
            return EXIT_FAILURE;
        }
    }

    free_word_table(&result);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}