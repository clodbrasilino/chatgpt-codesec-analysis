#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *word;
    size_t length;
    size_t count;
} WordCount;

static char *copy_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static void free_counts(WordCount *counts, size_t count)
{
    size_t i;

    if (counts == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(counts[i].word);
    }

    free(counts);
}

static int find_most_frequent_word(const char *const strings[],
                                   const size_t lengths[],
                                   size_t string_count,
                                   char **result,
                                   size_t *occurrences)
{
    WordCount *counts = NULL;
    size_t unique_count = 0;
    size_t capacity = 0;
    size_t best_index = 0;
    size_t i;

    if (strings == NULL || lengths == NULL || string_count == 0 ||
        result == NULL || occurrences == NULL) {
        return -1;
    }

    *result = NULL;
    *occurrences = 0;

    for (i = 0; i < string_count; ++i) {
        size_t found_index = unique_count;
        size_t j;

        if (strings[i] == NULL || lengths[i] == SIZE_MAX) {
            goto failure;
        }

        for (j = 0; j < unique_count; ++j) {
            if (counts[j].length == lengths[i] &&
                (lengths[i] == 0 ||
                 memcmp(counts[j].word, strings[i], lengths[i]) == 0)) {
                found_index = j;
                break;
            }
        }

        if (found_index != unique_count) {
            if (counts[found_index].count == SIZE_MAX) {
                goto failure;
            }

            ++counts[found_index].count;

            if (counts[found_index].count > counts[best_index].count) {
                best_index = found_index;
            }

            continue;
        }

        if (unique_count == capacity) {
            size_t new_capacity;
            WordCount *resized;

            if (capacity == 0) {
                new_capacity = 8;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto failure;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*counts)) {
                goto failure;
            }

            resized = realloc(counts, new_capacity * sizeof(*counts));
            if (resized == NULL) {
                goto failure;
            }

            counts = resized;
            capacity = new_capacity;
        }

        counts[unique_count].word = copy_string(strings[i], lengths[i]);
        if (counts[unique_count].word == NULL) {
            goto failure;
        }

        counts[unique_count].length = lengths[i];
        counts[unique_count].count = 1;

        if (unique_count == 0) {
            best_index = 0;
        }

        ++unique_count;
    }

    *result = copy_string(counts[best_index].word,
                          counts[best_index].length);
    if (*result == NULL) {
        goto failure;
    }

    *occurrences = counts[best_index].count;
    free_counts(counts, unique_count);
    return 0;

failure:
    free_counts(counts, unique_count);
    free(*result);
    *result = NULL;
    *occurrences = 0;
    return -1;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char orange[] = "orange";
    static const char grape[] = "grape";

    const char *strings[] = {
        apple,
        banana,
        apple,
        orange,
        banana,
        apple,
        grape,
        banana,
        apple
    };

    const size_t lengths[] = {
        sizeof(apple) - 1,
        sizeof(banana) - 1,
        sizeof(apple) - 1,
        sizeof(orange) - 1,
        sizeof(banana) - 1,
        sizeof(apple) - 1,
        sizeof(grape) - 1,
        sizeof(banana) - 1,
        sizeof(apple) - 1
    };

    const size_t string_count = sizeof(strings) / sizeof(strings[0]);
    char *word = NULL;
    size_t occurrences = 0;

    if (find_most_frequent_word(strings, lengths, string_count,
                                &word, &occurrences) != 0) {
        fputs("Unable to determine the most frequent word.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (printf("%.*s: %zu\n", (int)strlen(word), word, occurrences) < 0) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);
    return EXIT_SUCCESS;
}