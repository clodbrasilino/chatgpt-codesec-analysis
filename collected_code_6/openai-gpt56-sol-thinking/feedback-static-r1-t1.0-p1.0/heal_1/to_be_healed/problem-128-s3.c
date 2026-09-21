#include <stdio.h>
#include <string.h>

typedef enum {
    SHORTLIST_SUCCESS,
    SHORTLIST_INVALID_ARGUMENT,
    SHORTLIST_INSUFFICIENT_CAPACITY
} ShortlistStatus;

static ShortlistStatus shortlist_words(
    const char *const words[],
    size_t word_count,
    size_t minimum_length,
    const char *shortlist[],
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
        if (words[i] == NULL) {
            return SHORTLIST_INVALID_ARGUMENT;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(words[i]) > minimum_length) {
            ++required;
        }
    }

    if (required > shortlist_capacity) {
        return SHORTLIST_INSUFFICIENT_CAPACITY;
    }

    for (size_t i = 0; i < word_count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(words[i]) > minimum_length) {
            shortlist[*shortlist_count] = words[i];
            ++(*shortlist_count);
        }
    }

    return SHORTLIST_SUCCESS;
}

int main(void)
{
    enum { WORD_COUNT = 7 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *words[WORD_COUNT] = {
        "apple",
        "fig",
        "banana",
        "kiwi",
        "watermelon",
        "pear",
        "strawberry"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *shortlist[WORD_COUNT];
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
        if (fprintf(stderr, "Unable to shortlist words.\n") < 0) {
            return 1;
        }
        return 1;
    }

    for (size_t i = 0; i < shortlist_count; ++i) {
        if (printf("%s\n", shortlist[i]) < 0) {
            return 1;
        }
    }

    return 0;
}