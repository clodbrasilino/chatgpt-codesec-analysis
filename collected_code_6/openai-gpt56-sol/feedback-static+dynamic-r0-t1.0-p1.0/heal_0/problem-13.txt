#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    char *word;
    size_t count;
} WordCount;

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1U);
    return copy;
}

static void free_word_counts(WordCount *entries, size_t count)
{
    size_t i;

    if (entries == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        free(entries[i].word);
    }

    free(entries);
}

static int count_words(const char *const dictionary[],
                       size_t word_count,
                       WordCount **result,
                       size_t *result_count)
{
    WordCount *entries = NULL;
    size_t unique_count = 0U;
    size_t capacity = 0U;
    size_t i;

    if (dictionary == NULL || result == NULL || result_count == NULL) {
        return EINVAL;
    }

    *result = NULL;
    *result_count = 0U;

    for (i = 0U; i < word_count; ++i) {
        size_t j;

        if (dictionary[i] == NULL) {
            free_word_counts(entries, unique_count);
            return EINVAL;
        }

        for (j = 0U; j < unique_count; ++j) {
            if (strcmp(entries[j].word, dictionary[i]) == 0) {
                if (entries[j].count == SIZE_MAX) {
                    free_word_counts(entries, unique_count);
                    return EOVERFLOW;
                }

                ++entries[j].count;
                break;
            }
        }

        if (j == unique_count) {
            char *word_copy;

            if (unique_count == capacity) {
                size_t new_capacity;
                WordCount *resized_entries;

                if (capacity == 0U) {
                    new_capacity = 8U;
                } else {
                    if (capacity > SIZE_MAX / 2U) {
                        free_word_counts(entries, unique_count);
                        return EOVERFLOW;
                    }
                    new_capacity = capacity * 2U;
                }

                if (new_capacity > SIZE_MAX / sizeof(*entries)) {
                    free_word_counts(entries, unique_count);
                    return EOVERFLOW;
                }

                resized_entries = realloc(
                    entries, new_capacity * sizeof(*entries));
                if (resized_entries == NULL) {
                    free_word_counts(entries, unique_count);
                    return ENOMEM;
                }

                entries = resized_entries;
                capacity = new_capacity;
            }

            word_copy = duplicate_string(dictionary[i]);
            if (word_copy == NULL) {
                free_word_counts(entries, unique_count);
                return ENOMEM;
            }

            entries[unique_count].word = word_copy;
            entries[unique_count].count = 1U;
            ++unique_count;
        }
    }

    *result = entries;
    *result_count = unique_count;
    return 0;
}

static int print_most_common_words(const WordCount *entries, size_t count)
{
    size_t maximum = 0U;
    size_t i;

    if (entries == NULL && count != 0U) {
        return EINVAL;
    }

    for (i = 0U; i < count; ++i) {
        if (entries[i].word == NULL) {
            return EINVAL;
        }

        if (entries[i].count > maximum) {
            maximum = entries[i].count;
        }
    }

    if (maximum == 0U) {
        return 0;
    }

    for (i = 0U; i < count; ++i) {
        if (entries[i].count == maximum) {
            if (printf("%s: %zu\n", entries[i].word, entries[i].count) < 0) {
                return EIO;
            }
        }
    }

    return 0;
}

int main(void)
{
    static const char *const dictionary[] = {
        "apple", "banana", "apple", "orange", "banana",
        "apple", "pear", "banana", "grape"
    };
    WordCount *entries = NULL;
    size_t unique_count = 0U;
    int status;

    status = count_words(
        dictionary,
        sizeof(dictionary) / sizeof(dictionary[0]),
        &entries,
        &unique_count);
    if (status != 0) {
        fprintf(stderr, "Unable to count words: %s\n", strerror(status));
        return EXIT_FAILURE;
    }

    status = print_most_common_words(entries, unique_count);
    free_word_counts(entries, unique_count);

    if (status != 0) {
        fprintf(stderr, "Unable to print results: %s\n", strerror(status));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}