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
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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

static int grow_word_counts(WordCount **entries, size_t *capacity)
{
    size_t new_capacity;
    WordCount *resized_entries;

    if (entries == NULL || capacity == NULL) {
        return EINVAL;
    }

    if (*capacity == 0U) {
        new_capacity = 8U;
    } else {
        if (*capacity > SIZE_MAX / 2U) {
            return EOVERFLOW;
        }
        new_capacity = *capacity * 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(*resized_entries)) {
        return EOVERFLOW;
    }

    resized_entries = realloc(*entries,
                              new_capacity * sizeof(*resized_entries));
    if (resized_entries == NULL) {
        return ENOMEM;
    }

    *entries = resized_entries;
    *capacity = new_capacity;

    return 0;
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

    if (dictionary == NULL || word_lengths == NULL ||
        result == NULL || result_count == NULL) {
        return EINVAL;
    }

    *result = NULL;
    *result_count = 0U;

    for (i = 0U; i < word_count; ++i) {
        size_t actual_length;
        size_t j;

        if (dictionary[i] == NULL) {
            free_word_counts(entries, unique_count);
            return EINVAL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        actual_length = strlen(dictionary[i]);
        if (word_lengths[i] != actual_length) {
            free_word_counts(entries, unique_count);
            return EINVAL;
        }

        for (j = 0U; j < unique_count; ++j) {
            if (entries[j].length == actual_length &&
                memcmp(entries[j].word, dictionary[i], actual_length) == 0) {
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
                status = grow_word_counts(&entries, &capacity);
                if (status != 0) {
                    free_word_counts(entries, unique_count);
                    return status;
                }
            }

            status = duplicate_string(dictionary[i], actual_length, &word_copy);
            if (status != 0) {
                free_word_counts(entries, unique_count);
                return status;
            }

            entries[unique_count].word = word_copy;
            entries[unique_count].length = actual_length;
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

    for (i = 0U; i < count; ++i) {
        if (maximum != 0U && entries[i].count == maximum) {
            if (fwrite(entries[i].word, 1U, entries[i].length, stdout) !=
                entries[i].length) {
                return EIO;
            }

            if (fprintf(stdout, ": %zu\n", entries[i].count) < 0) {
                return EIO;
            }
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

    status = count_words(dictionary, word_lengths,
                         sizeof(dictionary) / sizeof(dictionary[0]),
                         &entries, &unique_count);
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