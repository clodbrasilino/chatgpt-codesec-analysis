#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int shortlist_words(const char *const words[],
                           const size_t word_sizes[],
                           size_t word_count,
                           size_t min_length,
                           const char ***result,
                           size_t *result_count)
{
    const char **shortlist;
    size_t count = 0;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (word_count == 0) {
        return 0;
    }

    if (words == NULL || word_sizes == NULL ||
        word_count > SIZE_MAX / sizeof(*shortlist)) {
        return -1;
    }

    shortlist = malloc(word_count * sizeof(*shortlist));
    if (shortlist == NULL) {
        return -1;
    }

    for (size_t i = 0; i < word_count; ++i) {
        const char *terminator;

        if (words[i] == NULL || word_sizes[i] == 0) {
            free(shortlist);
            return -1;
        }

        terminator = memchr(words[i], '\0', word_sizes[i]);
        if (terminator == NULL) {
            free(shortlist);
            return -1;
        }

        if ((size_t)(terminator - words[i]) > min_length) {
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
    static const char word0[] = "cat";
    static const char word1[] = "elephant";
    static const char word2[] = "dog";
    static const char word3[] = "giraffe";
    static const char word4[] = "antelope";
    static const char word5[] = "owl";

    const char *words[] = {
        word0, word1, word2, word3, word4, word5
    };
    const size_t word_sizes[] = {
        sizeof(word0), sizeof(word1), sizeof(word2),
        sizeof(word3), sizeof(word4), sizeof(word5)
    };
    const size_t word_count = sizeof(words) / sizeof(words[0]);
    const size_t min_length = 5;
    const char **shortlist = NULL;
    size_t shortlist_count = 0;

    if (shortlist_words(words, word_sizes, word_count, min_length,
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