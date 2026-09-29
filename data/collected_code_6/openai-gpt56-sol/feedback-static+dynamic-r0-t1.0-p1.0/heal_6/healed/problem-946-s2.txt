#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    size_t length;
    size_t count;
} WordCount;

static void free_word_counts(WordCount *items, size_t count)
{
    if (items == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(items[i].word);
    }

    free(items);
}

static int ensure_word_capacity(WordCount **items, size_t *capacity,
                                size_t required)
{
    if (items == NULL || capacity == NULL || required == 0) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    size_t new_capacity = (*capacity == 0) ? 16 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity < required ||
        new_capacity > SIZE_MAX / sizeof(**items)) {
        return -1;
    }

    WordCount *resized = realloc(*items,
                                 new_capacity * sizeof(**items));
    if (resized == NULL) {
        return -1;
    }

    *items = resized;
    *capacity = new_capacity;
    return 0;
}

static int copy_word(char **destination, const char *source, size_t length)
{
    if (destination == NULL || source == NULL || length == 0) {
        return -1;
    }

    *destination = NULL;

    if (length > SIZE_MAX - 1) {
        return -1;
    }

    size_t allocation_size = length + 1;
    char *copy = malloc(allocation_size);

    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, source, length);
    copy[length] = '\0';
    *destination = copy;

    return 0;
}

static int add_word(WordCount **items, size_t *count, size_t *capacity,
                    const char *word, size_t length)
{
    if (items == NULL || count == NULL || capacity == NULL ||
        word == NULL || length == 0 || *count > *capacity ||
        (*count != 0 && *items == NULL)) {
        return -1;
    }

    for (size_t i = 0; i < *count; ++i) {
        if ((*items)[i].length == length &&
            memcmp((*items)[i].word, word, length) == 0) {
            if ((*items)[i].count == SIZE_MAX) {
                return -1;
            }

            ++(*items)[i].count;
            return 0;
        }
    }

    if (*count == SIZE_MAX) {
        return -1;
    }

    if (ensure_word_capacity(items, capacity, *count + 1) != 0) {
        return -1;
    }

    char *copy = NULL;

    if (copy_word(&copy, word, length) != 0) {
        return -1;
    }

    (*items)[*count].word = copy;
    (*items)[*count].length = length;
    (*items)[*count].count = 1;
    ++*count;

    return 0;
}

static int find_most_common(const char *text, WordCount **results,
                            size_t *result_count)
{
    if (text == NULL || results == NULL || result_count == NULL) {
        return -1;
    }

    *results = NULL;
    *result_count = 0;

    WordCount *items = NULL;
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

        if (length == 0) {
            continue;
        }

        if (length > SIZE_MAX - 1) {
            free_word_counts(items, count);
            return -1;
        }

        size_t allocation_size = length + 1;
        char *normalized = malloc(allocation_size);

        if (normalized == NULL) {
            free_word_counts(items, count);
            return -1;
        }

        for (size_t i = 0; i < length; ++i) {
            normalized[i] = (char)tolower((unsigned char)start[i]);
        }

        normalized[length] = '\0';

        int status = add_word(&items, &count, &capacity,
                              normalized, length);
        free(normalized);

        if (status != 0) {
            free_word_counts(items, count);
            return -1;
        }
    }

    if (count == 0) {
        free(items);
        return 0;
    }

    size_t maximum = items[0].count;

    for (size_t i = 1; i < count; ++i) {
        if (items[i].count > maximum) {
            maximum = items[i].count;
        }
    }

    size_t matches = 0;

    for (size_t i = 0; i < count; ++i) {
        if (items[i].count == maximum) {
            if (matches == SIZE_MAX) {
                free_word_counts(items, count);
                return -1;
            }

            ++matches;
        }
    }

    if (matches == 0 ||
        matches > SIZE_MAX / sizeof(WordCount)) {
        free_word_counts(items, count);
        return -1;
    }

    WordCount *common = calloc(matches, sizeof(*common));

    if (common == NULL) {
        free_word_counts(items, count);
        return -1;
    }

    size_t result_index = 0;

    for (size_t i = 0; i < count; ++i) {
        if (items[i].count == maximum) {
            common[result_index] = items[i];
            items[i].word = NULL;
            ++result_index;
        }
    }

    free_word_counts(items, count);

    *results = common;
    *result_count = result_index;
    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    if (buffer == NULL || capacity == NULL || required == 0) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    size_t new_capacity = (*capacity == 0) ? 4096 : *capacity;

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

    char *resized = realloc(*buffer, new_capacity);

    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_input(char **output)
{
    if (output == NULL) {
        return -1;
    }

    *output = NULL;

    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;

    for (;;) {
        if (length > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        if (grow_buffer(&buffer, &capacity, length + 2) != 0) {
            free(buffer);
            return -1;
        }

        size_t available = capacity - length - 1;

        if (available == 0) {
            free(buffer);
            return -1;
        }

        size_t bytes_read = fread(buffer + length, 1, available, stdin);

        if (bytes_read > available ||
            length > SIZE_MAX - bytes_read) {
            free(buffer);
            return -1;
        }

        length += bytes_read;

        if (bytes_read < available) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }

            if (feof(stdin)) {
                break;
            }

            if (bytes_read == 0) {
                free(buffer);
                return -1;
            }
        }
    }

    buffer[length] = '\0';
    *output = buffer;
    return 0;
}

int main(void)
{
    char *text = NULL;

    if (read_input(&text) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    WordCount *results = NULL;
    size_t result_count = 0;

    if (find_most_common(text, &results, &result_count) != 0) {
        free(text);
        fputs("Failed to process text.\n", stderr);
        return EXIT_FAILURE;
    }

    free(text);

    for (size_t i = 0; i < result_count; ++i) {
        if (printf("%s: %zu\n",
                   results[i].word,
                   results[i].count) < 0) {
            free_word_counts(results, result_count);
            return EXIT_FAILURE;
        }
    }

    free_word_counts(results, result_count);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}