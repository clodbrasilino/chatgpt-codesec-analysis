#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_size(const char *text, size_t *value)
{
    size_t result = 0;
    const unsigned char *current;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    current = (const unsigned char *)text;

    while (*current != '\0') {
        size_t digit;

        if (*current < '0' || *current > '9') {
            return 0;
        }

        digit = (size_t)(*current - '0');

        if (result > (SIZE_MAX - digit) / 10U) {
            return 0;
        }

        result = result * 10U + digit;
        ++current;
    }

    *value = result;
    return 1;
}

static void free_word_list(char **words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(words[i]);
    }

    free(words);
}

static int shortlist_words(char *const *words, size_t word_count, size_t n,
                           char ***out_words, size_t *out_count)
{
    char **result;
    size_t match_count = 0;
    size_t selected = 0;
    size_t i;

    if (out_words == NULL || out_count == NULL) {
        return 0;
    }

    *out_words = NULL;
    *out_count = 0;

    if (words == NULL && word_count != 0U) {
        return 0;
    }

    for (i = 0; i < word_count; ++i) {
        if (words[i] == NULL) {
            return 0;
        }

        if (strlen(words[i]) > n) {
            ++match_count;
        }
    }

    if (match_count == 0U) {
        return 1;
    }

    if (match_count > SIZE_MAX / sizeof(*result)) {
        return 0;
    }

    result = calloc(match_count, sizeof(*result));
    if (result == NULL) {
        return 0;
    }

    for (i = 0; i < word_count; ++i) {
        size_t length = strlen(words[i]);

        if (length > n) {
            if (length == SIZE_MAX) {
                free_word_list(result, selected);
                return 0;
            }

            result[selected] = malloc(length + 1U);
            if (result[selected] == NULL) {
                free_word_list(result, selected);
                return 0;
            }

            memcpy(result[selected], words[i], length + 1U);
            ++selected;
        }
    }

    *out_words = result;
    *out_count = selected;
    return 1;
}

int main(int argc, char *argv[])
{
    char **shortlisted = NULL;
    size_t shortlisted_count = 0;
    size_t n;
    size_t i;
    int status = EXIT_SUCCESS;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s n word [word ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_size(argv[1], &n)) {
        fputs("Invalid value for n\n", stderr);
        return EXIT_FAILURE;
    }

    if (!shortlist_words(argv + 2, (size_t)(argc - 2), n,
                         &shortlisted, &shortlisted_count)) {
        fputs("Unable to shortlist words\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < shortlisted_count; ++i) {
        if (puts(shortlisted[i]) == EOF) {
            status = EXIT_FAILURE;
            break;
        }
    }

    free_word_list(shortlisted, shortlisted_count);
    return status;
}