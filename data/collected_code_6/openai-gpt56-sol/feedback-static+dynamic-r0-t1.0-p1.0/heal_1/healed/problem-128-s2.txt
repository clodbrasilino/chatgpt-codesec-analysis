#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int shortlist_words(const char *const words[],
                           const size_t word_lengths[],
                           size_t word_count,
                           size_t min_length,
                           const char ***result,
                           size_t *result_count)
{
    const char **matches = NULL;
    size_t count = 0;

    if (result == NULL || result_count == NULL ||
        (word_count > 0 && (words == NULL || word_lengths == NULL))) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    for (size_t i = 0; i < word_count; ++i) {
        if (words[i] == NULL) {
            return -1;
        }

        if (word_lengths[i] > min_length) {
            ++count;
        }
    }

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*matches)) {
        return -1;
    }

    matches = malloc(count * sizeof(*matches));
    if (matches == NULL) {
        return -1;
    }

    size_t match_index = 0;

    for (size_t i = 0; i < word_count; ++i) {
        if (word_lengths[i] > min_length) {
            matches[match_index++] = words[i];
        }
    }

    *result = matches;
    *result_count = count;
    return 0;
}

int main(void)
{
    static const char word_0[] = "apple";
    static const char word_1[] = "fig";
    static const char word_2[] = "banana";
    static const char word_3[] = "pear";
    static const char word_4[] = "watermelon";
    static const char word_5[] = "kiwi";

    const char *words[] = {
        word_0,
        word_1,
        word_2,
        word_3,
        word_4,
        word_5
    };

    const size_t word_lengths[] = {
        sizeof(word_0) - 1,
        sizeof(word_1) - 1,
        sizeof(word_2) - 1,
        sizeof(word_3) - 1,
        sizeof(word_4) - 1,
        sizeof(word_5) - 1
    };

    const size_t word_count = sizeof(words) / sizeof(words[0]);
    const size_t min_length = 4;
    const char **shortlisted = NULL;
    size_t shortlisted_count = 0;

    if (shortlist_words(words, word_lengths, word_count, min_length,
                        &shortlisted, &shortlisted_count) != 0) {
        fputs("Failed to shortlist words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < shortlisted_count; ++i) {
        if (printf("%.*s\n",
                   (int)word_lengths[shortlisted[i] - words[0]],
                   shortlisted[i]) < 0) {
            free(shortlisted);
            return EXIT_FAILURE;
        }
    }

    free(shortlisted);
    return EXIT_SUCCESS;
}