#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    size_t length;
    size_t count;
} WordCount;

static int duplicate_string(const char *source, size_t source_length,
                            char **destination)
{
    char *copy;

    if (source == NULL || destination == NULL) {
        return EINVAL;
    }

    *destination = NULL;

    if (source_length == SIZE_MAX) {
        return EOVERFLOW;
    }

    copy = malloc(source_length + 1U);
    if (copy == NULL) {
        return ENOMEM;
    }

    if (source_length > 0U) {
        memcpy(copy, source, source_length);
    }

    copy[source_length] = '\0';
    *destination = copy;

    return 0;
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
                       const size_t word_lengths[],
                       size_t word_count,
                       WordCount **result,
                       size_t *result_count)
{
    WordCount *entries = NULL;
    size_t unique_count = 0U;
    size_t capacity = 0U;
    size_t i;

    if (result == NULL || result_count == NULL) {
        return EINVAL;
    }

    *result = NULL;
    *result_count = 0U;

    if (word_count != 0U &&
        (dictionary == NULL || word_lengths == NULL)) {
        return EINVAL;
    }

    for (i = 0U; i < word_count; ++i) {
        size_t j;
        size_t length = word_lengths[i];

        if (dictionary[i] == NULL) {
            free_word_counts(entries, unique_count);
            return EINVAL;
        }

        for (j = 0U; j < unique_count; ++j) {
            if (entries[j].length == length &&
                (length == 0U ||
                 memcmp(entries[j].word, dictionary[i], length) == 0)) {
                if (entries[j].count == SIZE_MAX) {
                    free_word_counts(entries, unique_count);
                    return EOVERFLOW;
                }

                ++entries[j].count;
                break;
            }
        }

        if (j == unique_count) {
            char *word_copy = NULL;
            int status;

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

                resized_entries =
                    realloc(entries, new_capacity * sizeof(*entries));
                if (resized_entries == NULL) {
                    free_word_counts(entries, unique_count);
                    return ENOMEM;
                }

                entries = resized_entries;
                capacity = new_capacity;
            }

            status = duplicate_string(dictionary[i], length, &word_copy);
            if (status != 0) {
                free_word_counts(entries, unique_count);
                return status;
            }

            entries[unique_count].word = word_copy;
            entries[unique_count].length = length;
            entries[unique_count].count = 1U;
            ++unique_count;
        }
    }

    *result = entries;
    *result_count = unique_count;

    return 0;
}

static int print_word(const char *word, size_t length, size_t count)
{
    size_t written;

    if (word == NULL) {
        return EINVAL;
    }

    if (length != 0U) {
        written = fwrite(word, 1U, length, stdout);
        if (written != length) {
            return EIO;
        }
    }

    if (fprintf(stdout, ": %zu\n", count) < 0) {
        return EIO;
    }

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
        if (entries[i].word == NULL || entries[i].count == 0U) {
            return EINVAL;
        }

        if (entries[i].count > maximum) {
            maximum = entries[i].count;
        }
    }

    for (i = 0U; i < count; ++i) {
        int status;

        if (entries[i].count != maximum) {
            continue;
        }

        status = print_word(entries[i].word, entries[i].length,
                            entries[i].count);
        if (status != 0) {
            return status;
        }
    }

    return 0;
}

int main(void)
{
    static const char *const dictionary[] = {
        "apple",
        "banana",
        "apple",
        "orange",
        "banana",
        "apple",
        "pear",
        "banana",
        "grape"
    };
    static const size_t word_lengths[] = {
        sizeof("apple") - 1U,
        sizeof("banana") - 1U,
        sizeof("apple") - 1U,
        sizeof("orange") - 1U,
        sizeof("banana") - 1U,
        sizeof("apple") - 1U,
        sizeof("pear") - 1U,
        sizeof("banana") - 1U,
        sizeof("grape") - 1U
    };
    WordCount *entries = NULL;
    size_t unique_count = 0U;
    int status;

    status = count_words(dictionary,
                         word_lengths,
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