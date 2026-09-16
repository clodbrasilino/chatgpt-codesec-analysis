#include <ctype.h>
#include <errno.h>
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

static char *copy_word_lowercase(const char *start, size_t length)
{
    if (length == SIZE_MAX) {
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
    char *word = copy_word_lowercase(start, length);
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
        size_t new_capacity = *capacity == 0 ? 16 : *capacity * 2;

        if (new_capacity < *capacity ||
            new_capacity > SIZE_MAX / sizeof(**words)) {
            free(word);
            return -1;
        }

        WordCount *resized = realloc(*words, new_capacity * sizeof(*resized));
        if (resized == NULL) {
            free(word);
            return -1;
        }

        *words = resized;
        *capacity = new_capacity;
    }

    (*words)[*count].word = word;
    (*words)[*count].count = 1;
    ++(*count);
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

    qsort(words, count, sizeof(*words), compare_word_counts);

    if (n < count) {
        for (size_t i = n; i < count; ++i) {
            free(words[i].word);
        }
        count = n;
    }

    if (count == 0) {
        free(words);
        words = NULL;
    } else {
        WordCount *resized = realloc(words, count * sizeof(*resized));
        if (resized != NULL) {
            words = resized;
        }
    }

    *result = words;
    *result_count = count;
    return 0;
}

static int read_all_text(FILE *stream, char **text)
{
    if (stream == NULL || text == NULL) {
        return -1;
    }

    *text = NULL;
    size_t length = 0;
    size_t capacity = 4096;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            size_t new_capacity = capacity * 2;
            char *resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        size_t available = capacity - length - 1;
        size_t received = fread(buffer + length, 1, available, stream);
        length += received;

        if (received < available) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            if (feof(stream)) {
                break;
            }
        }
    }

    buffer[length] = '\0';
    *text = buffer;
    return 0;
}

static int parse_size(const char *value, size_t *result)
{
    if (value == NULL || result == NULL || *value == '\0' || *value == '-') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long parsed = strtoull(value, &end, 10);

    if (errno != 0 || end == value || *end != '\0' ||
        parsed > (unsigned long long)SIZE_MAX) {
        return -1;
    }

    *result = (size_t)parsed;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n < input.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t n = 0;
    if (parse_size(argv[1], &n) != 0) {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    char *text = NULL;
    if (read_all_text(stdin, &text) != 0) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    WordCount *results = NULL;
    size_t result_count = 0;

    if (find_most_common_words(text, n, &results, &result_count) != 0) {
        fprintf(stderr, "Failed to count words\n");
        free(text);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; ++i) {
        if (printf("%s %zu\n", results[i].word, results[i].count) < 0) {
            fprintf(stderr, "Failed to write output\n");
            free_word_counts(results, result_count);
            free(text);
            return EXIT_FAILURE;
        }
    }

    free_word_counts(results, result_count);
    free(text);

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to flush output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}