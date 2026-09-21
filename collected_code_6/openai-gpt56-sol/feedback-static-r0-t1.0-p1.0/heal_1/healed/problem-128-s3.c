#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int shortlist_words(const char *const words[],
                           const size_t word_lengths[],
                           size_t word_count,
                           size_t min_length,
                           const char ***result,
                           size_t *result_count)
{
    const char **shortlist;
    size_t count = 0;

    if (words == NULL || word_lengths == NULL ||
        result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (word_count == 0) {
        return 0;
    }

    if (word_count > SIZE_MAX / sizeof(*shortlist)) {
        return -1;
    }

    shortlist = malloc(word_count * sizeof(*shortlist));
    if (shortlist == NULL) {
        return -1;
    }

    for (size_t i = 0; i < word_count; ++i) {
        if (words[i] == NULL ||
            memchr(words[i], '\0', word_lengths[i] + 1) == NULL) {
            free(shortlist);
            return -1;
        }

        if (word_lengths[i] > min_length) {
            shortlist[count++] = words[i];
        }
    }

    if (count == 0) {
        free(shortlist);
        return 0;
    }

    *result = shortlist;
    *result_count = count;
    return 0;
}

int main(void)
{
    const char *words[] = {
        "cat",
        "elephant",
        "dog",
        "giraffe",
        "antelope",
        "owl"
    };
    const size_t word_lengths[] = {
        sizeof("cat") - 1,
        sizeof("elephant") - 1,
        sizeof("dog") - 1,
        sizeof("giraffe") - 1,
        sizeof("antelope") - 1,
        sizeof("owl") - 1
    };
    const size_t word_count = sizeof(words) / sizeof(words[0]);
    const size_t min_length = 5;
    const char **shortlist = NULL;
    size_t shortlist_count = 0;

    if (shortlist_words(words, word_lengths, word_count, min_length,
                        &shortlist, &shortlist_count) != 0) {
        fputs("Failed to shortlist words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < shortlist_count; ++i) {
        if (puts(shortlist[i]) == EOF) {
            free(shortlist);
            return EXIT_FAILURE;
        }
    }

    free(shortlist);
    return EXIT_SUCCESS;
}