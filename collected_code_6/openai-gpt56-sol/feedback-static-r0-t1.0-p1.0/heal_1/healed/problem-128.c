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
    size_t i;

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

    for (i = 0; i < word_count; ++i) {
        if (words[i] == NULL) {
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
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char kiwi[] = "kiwi";
    static const char strawberry[] = "strawberry";
    static const char pear[] = "pear";
    static const char watermelon[] = "watermelon";

    const char *words[] = {
        apple,
        banana,
        kiwi,
        strawberry,
        pear,
        watermelon
    };

    const size_t word_lengths[] = {
        sizeof(apple) - 1,
        sizeof(banana) - 1,
        sizeof(kiwi) - 1,
        sizeof(strawberry) - 1,
        sizeof(pear) - 1,
        sizeof(watermelon) - 1
    };

    const char **shortlist = NULL;
    size_t shortlist_count = 0;
    const size_t min_length = 5;
    size_t i;
    int status;

    status = shortlist_words(
        words,
        word_lengths,
        sizeof(words) / sizeof(words[0]),
        min_length,
        &shortlist,
        &shortlist_count
    );

    if (status != 0) {
        fprintf(stderr, "Failed to shortlist words.\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < shortlist_count; ++i) {
        if (printf("%s\n", shortlist[i]) < 0) {
            free(shortlist);
            return EXIT_FAILURE;
        }
    }

    free(shortlist);
    return EXIT_SUCCESS;
}