#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum shortlist_status {
    SHORTLIST_SUCCESS,
    SHORTLIST_INVALID_ARGUMENT,
    SHORTLIST_ALLOCATION_FAILURE,
    SHORTLIST_SIZE_ERROR
};

static enum shortlist_status shortlist_words(
    char *const words[],
    size_t word_count,
    size_t minimum_length,
    const char ***selected_words,
    size_t *selected_count)
{
    const char **result;
    size_t count = 0;
    size_t i;

    if (selected_words == NULL || selected_count == NULL) {
        return SHORTLIST_INVALID_ARGUMENT;
    }

    *selected_words = NULL;
    *selected_count = 0;

    if (word_count == 0) {
        return SHORTLIST_SUCCESS;
    }

    if (words == NULL) {
        return SHORTLIST_INVALID_ARGUMENT;
    }

    if (word_count > SIZE_MAX / sizeof(*result)) {
        return SHORTLIST_SIZE_ERROR;
    }

    result = malloc(word_count * sizeof(*result));
    if (result == NULL) {
        return SHORTLIST_ALLOCATION_FAILURE;
    }

    for (i = 0; i < word_count; ++i) {
        if (words[i] == NULL) {
            free(result);
            return SHORTLIST_INVALID_ARGUMENT;
        }

        if (strlen(words[i]) > minimum_length) {
            result[count++] = words[i];
        }
    }

    if (count == 0) {
        free(result);
        result = NULL;
    }

    *selected_words = result;
    *selected_count = count;

    return SHORTLIST_SUCCESS;
}

int main(int argc, char *argv[])
{
    const char **selected_words = NULL;
    size_t selected_count = 0;
    size_t word_count;
    size_t minimum_length;
    uintmax_t parsed_length;
    char *end;
    enum shortlist_status status;
    size_t i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s n [word ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] < '0' || argv[1][0] > '9') {
        fprintf(stderr, "Invalid length: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_length = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        parsed_length > SIZE_MAX) {
        fprintf(stderr, "Invalid length: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    minimum_length = (size_t)parsed_length;
    word_count = (size_t)(argc - 2);

    status = shortlist_words(
        argv + 2,
        word_count,
        minimum_length,
        &selected_words,
        &selected_count);

    if (status != SHORTLIST_SUCCESS) {
        fprintf(stderr, "Unable to shortlist words\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < selected_count; ++i) {
        if (puts(selected_words[i]) == EOF) {
            free(selected_words);
            return EXIT_FAILURE;
        }
    }

    free(selected_words);
    return EXIT_SUCCESS;
}