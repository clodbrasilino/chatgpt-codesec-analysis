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

    for (size_t i = 0U; i < count; ++i) {
        free(items[i].word);
    }

    free(items);
}

static int ensure_word_capacity(WordCount **items, size_t *capacity,
                                size_t required)
{
    if (items == NULL || capacity == NULL ||
        (*capacity != 0U && *items == NULL)) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    size_t new_capacity = (*capacity == 0U) ? 16U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof **items) {
        return -1;
    }

    WordCount *resized = realloc(*items, new_capacity * sizeof **items);
    if (resized == NULL) {
        return -1;
    }

    *items = resized;
    *capacity = new_capacity;
    return 0;
}

static int add_word(WordCount **items, size_t *count, size_t *capacity,
                    const char *word, size_t length)
{
    if (items == NULL || count == NULL || capacity == NULL || word == NULL ||
        *count > *capacity || (*capacity != 0U && *items == NULL)) {
        return -1;
    }

    for (size_t i = 0U; i < *count; ++i) {
        if ((*items)[i].length == length &&
            memcmp((*items)[i].word, word, length) == 0) {
            if ((*items)[i].count == SIZE_MAX) {
                return -1;
            }

            ++(*items)[i].count;
            return 0;
        }
    }

    if (*count == SIZE_MAX ||
        ensure_word_capacity(items, capacity, *count + 1U) != 0) {
        return -1;
    }

    if (length == SIZE_MAX) {
        return -1;
    }

    size_t allocation_size = length + 1U;
    char *copy = malloc(allocation_size);
    if (copy == NULL) {
        return -1;
    }

    if (length != 0U) {
        memcpy(copy, word, length);
    }
    copy[length] = '\0';

    (*items)[*count].word = copy;
    (*items)[*count].length = length;
    (*items)[*count].count = 1U;
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
    *result_count = 0U;

    WordCount *items = NULL;
    size_t count = 0U;
    size_t capacity = 0U;
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
        if (length == 0U) {
            continue;
        }

        if (length == SIZE_MAX) {
            free_word_counts(items, count);
            return -1;
        }

        char *normalized = malloc(length + 1U);
        if (normalized == NULL) {
            free_word_counts(items, count);
            return -1;
        }

        for (size_t i = 0U; i < length; ++i) {
            normalized[i] = (char)tolower((unsigned char)start[i]);
        }
        normalized[length] = '\0';

        if (add_word(&items, &count, &capacity, normalized, length) != 0) {
            free(normalized);
            free_word_counts(items, count);
            return -1;
        }

        free(normalized);
    }

    if (count == 0U) {
        free(items);
        return 0;
    }

    size_t maximum = items[0].count;
    for (size_t i = 1U; i < count; ++i) {
        if (items[i].count > maximum) {
            maximum = items[i].count;
        }
    }

    size_t matches = 0U;
    for (size_t i = 0U; i < count; ++i) {
        if (items[i].count == maximum) {
            if (matches == SIZE_MAX) {
                free_word_counts(items, count);
                return -1;
            }
            ++matches;
        }
    }

    if (matches > SIZE_MAX / sizeof(WordCount)) {
        free_word_counts(items, count);
        return -1;
    }

    WordCount *common = malloc(matches * sizeof *common);
    if (common == NULL) {
        free_word_counts(items, count);
        return -1;
    }

    size_t result_index = 0U;
    for (size_t i = 0U; i < count; ++i) {
        if (items[i].count == maximum) {
            common[result_index] = items[i];
            items[i].word = NULL;
            ++result_index;
        }
    }

    free_word_counts(items, count);

    *results = common;
    *result_count = matches;
    return 0;
}

static int ensure_buffer_capacity(char **buffer, size_t *capacity,
                                  size_t required)
{
    if (buffer == NULL || capacity == NULL || required == 0U ||
        (*capacity != 0U && *buffer == NULL)) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    size_t new_capacity = (*capacity == 0U) ? 4096U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    char *resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_input(FILE *stream, char **output)
{
    if (stream == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    char *buffer = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    unsigned char chunk[4096];

    for (;;) {
        size_t bytes_read = fread(chunk, 1U, sizeof chunk, stream);

        if (bytes_read != 0U) {
            if (length > SIZE_MAX - bytes_read - 1U) {
                free(buffer);
                return -1;
            }

            size_t required = length + bytes_read + 1U;
            if (ensure_buffer_capacity(&buffer, &capacity, required) != 0) {
                free(buffer);
                return -1;
            }

            memcpy(buffer + length, chunk, bytes_read);
            length += bytes_read;
        }

        if (bytes_read < sizeof chunk) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            if (feof(stream)) {
                break;
            }
        }
    }

    if (ensure_buffer_capacity(&buffer, &capacity, length + 1U) != 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *output = buffer;
    return 0;
}

int main(void)
{
    char *text = NULL;

    if (read_input(stdin, &text) != 0) {
        fputs("Failed to read input or allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    WordCount *results = NULL;
    size_t result_count = 0U;

    if (find_most_common(text, &results, &result_count) != 0) {
        free(text);
        fputs("Failed to process text.\n", stderr);
        return EXIT_FAILURE;
    }

    free(text);

    for (size_t i = 0U; i < result_count; ++i) {
        if (printf("%s: %zu\n", results[i].word, results[i].count) < 0) {
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