#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char *word;
    size_t count;
} WordCount;

static int compare_word_counts(const void *lhs, const void *rhs)
{
    const WordCount *a = lhs;
    const WordCount *b = rhs;

    if (a->count < b->count) {
        return 1;
    }

    if (a->count > b->count) {
        return -1;
    }

    return strcmp(a->word, b->word);
}

static int count_most_common_words(const char *const dictionary[],
                                   size_t dictionary_size,
                                   size_t limit)
{
    WordCount *counts;
    size_t unique_count = 0U;
    size_t i;

    if (dictionary == NULL && dictionary_size != 0U) {
        return EXIT_FAILURE;
    }

    if (dictionary_size == 0U || limit == 0U) {
        return EXIT_SUCCESS;
    }

    if (dictionary_size > SIZE_MAX / sizeof(*counts)) {
        return EXIT_FAILURE;
    }

    counts = calloc(dictionary_size, sizeof(*counts));
    if (counts == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < dictionary_size; ++i) {
        size_t j;

        if (dictionary[i] == NULL) {
            free(counts);
            return EXIT_FAILURE;
        }

        for (j = 0U; j < unique_count; ++j) {
            if (strcmp(counts[j].word, dictionary[i]) == 0) {
                if (counts[j].count == SIZE_MAX) {
                    free(counts);
                    return EXIT_FAILURE;
                }

                ++counts[j].count;
                break;
            }
        }

        if (j == unique_count) {
            counts[unique_count].word = dictionary[i];
            counts[unique_count].count = 1U;
            ++unique_count;
        }
    }

    qsort(counts, unique_count, sizeof(*counts), compare_word_counts);

    if (limit > unique_count) {
        limit = unique_count;
    }

    for (i = 0U; i < limit; ++i) {
        if (printf("%s: %zu\n", counts[i].word, counts[i].count) < 0) {
            free(counts);
            return EXIT_FAILURE;
        }
    }

    free(counts);
    return EXIT_SUCCESS;
}

int main(void)
{
    const char *const dictionary[] = {
        "apple",
        "banana",
        "apple",
        "orange",
        "banana",
        "apple",
        "pear",
        "orange",
        "banana",
        "grape"
    };
    const size_t dictionary_size =
        sizeof(dictionary) / sizeof(dictionary[0]);
    const size_t number_to_print = 3U;

    return count_most_common_words(dictionary,
                                   dictionary_size,
                                   number_to_print);
}