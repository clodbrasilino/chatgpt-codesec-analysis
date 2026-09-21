#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SHORTLIST_SUCCESS,
    SHORTLIST_INVALID_ARGUMENT,
    SHORTLIST_INSUFFICIENT_CAPACITY
} ShortlistStatus;

typedef struct {
    const char *data;
    size_t length;
} Word;

static ShortlistStatus shortlist_words(
    const Word *words,
    size_t word_count,
    size_t minimum_length,
    const Word **shortlist,
    size_t shortlist_capacity,
    size_t *shortlist_count)
{
    size_t required = 0;

    if (shortlist_count == NULL ||
        (word_count > 0 && words == NULL) ||
        (shortlist_capacity > 0 && shortlist == NULL)) {
        return SHORTLIST_INVALID_ARGUMENT;
    }

    *shortlist_count = 0;

    for (size_t i = 0; i < word_count; ++i) {
        if (words[i].data == NULL) {
            return SHORTLIST_INVALID_ARGUMENT;
        }

        if (words[i].length > minimum_length) {
            ++required;
        }
    }

    if (required > shortlist_capacity) {
        return SHORTLIST_INSUFFICIENT_CAPACITY;
    }

    for (size_t i = 0; i < word_count; ++i) {
        if (words[i].length > minimum_length) {
            shortlist[*shortlist_count] = &words[i];
            ++(*shortlist_count);
        }
    }

    return SHORTLIST_SUCCESS;
}

int main(void)
{
    enum { WORD_COUNT = 7 };

    Word *words = malloc(WORD_COUNT * sizeof *words);
    const Word **shortlist = malloc(WORD_COUNT * sizeof *shortlist);

    if (words == NULL || shortlist == NULL) {
        free(shortlist);
        free(words);
        return 1;
    }

    words[0] = (Word){"apple", sizeof "apple" - 1};
    words[1] = (Word){"fig", sizeof "fig" - 1};
    words[2] = (Word){"banana", sizeof "banana" - 1};
    words[3] = (Word){"kiwi", sizeof "kiwi" - 1};
    words[4] = (Word){"watermelon", sizeof "watermelon" - 1};
    words[5] = (Word){"pear", sizeof "pear" - 1};
    words[6] = (Word){"strawberry", sizeof "strawberry" - 1};

    const size_t minimum_length = 5;
    size_t shortlist_count = 0;

    ShortlistStatus status = shortlist_words(
        words,
        WORD_COUNT,
        minimum_length,
        shortlist,
        WORD_COUNT,
        &shortlist_count
    );

    if (status != SHORTLIST_SUCCESS) {
        fputs("Unable to shortlist words.\n", stderr);
        free(shortlist);
        free(words);
        return 1;
    }

    for (size_t i = 0; i < shortlist_count; ++i) {
        if (fwrite(
                shortlist[i]->data,
                sizeof shortlist[i]->data[0],
                shortlist[i]->length,
                stdout) != shortlist[i]->length ||
            fputc('\n', stdout) == EOF) {
            free(shortlist);
            free(words);
            return 1;
        }
    }

    free(shortlist);
    free(words);
    return 0;
}