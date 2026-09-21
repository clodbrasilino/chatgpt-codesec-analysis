#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct word_view {
    const char *data;
    size_t length;
};

static int parse_size(const char *text, size_t *value)
{
    const unsigned char *current;
    size_t result = 0;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return 0;
    }

    current = (const unsigned char *)text;

    while (*current != '\0') {
        size_t digit;

        if (*current < (unsigned char)'0' ||
            *current > (unsigned char)'9') {
            return 0;
        }

        digit = (size_t)(*current - (unsigned char)'0');

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

static int shortlist_words(const struct word_view *words,
                           size_t word_count,
                           size_t minimum_length,
                           char ***out_words,
                           size_t *out_count)
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
        if (words[i].data == NULL) {
            return 0;
        }

        if (words[i].length > minimum_length) {
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
        size_t length;

        if (words[i].length <= minimum_length) {
            continue;
        }

        length = words[i].length;

        if (length == SIZE_MAX) {
            free_word_list(result, selected);
            return 0;
        }

        result[selected] = malloc(length + 1U);
        if (result[selected] == NULL) {
            free_word_list(result, selected);
            return 0;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[selected], words[i].data, length);
        result[selected][length] = '\0';
        ++selected;
    }

    *out_words = result;
    *out_count = selected;
    return 1;
}

int main(int argc, char **argv)
{
    struct word_view *words;
    char **shortlisted = NULL;
    size_t shortlisted_count = 0;
    size_t word_count;
    size_t minimum_length;
    size_t i;
    int status = EXIT_SUCCESS;

    if (argc < 3) {
        const char *program_name = "program";

        if (argc > 0 && argv != NULL &&
            argv[0] != NULL && argv[0][0] != '\0') {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s n word [word ...]\n", program_name);
        return EXIT_FAILURE;
    }

    if (argv == NULL || argv[1] == NULL ||
        !parse_size(argv[1], &minimum_length)) {
        fputs("Invalid value for n\n", stderr);
        return EXIT_FAILURE;
    }

    word_count = (size_t)(argc - 2);

    if (word_count > SIZE_MAX / sizeof(*words)) {
        fputs("Too many words\n", stderr);
        return EXIT_FAILURE;
    }

    words = malloc(word_count * sizeof(*words));
    if (words == NULL) {
        fputs("Unable to allocate word list\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < word_count; ++i) {
        const char *argument = argv[i + 2U];

        if (argument == NULL) {
            free(words);
            fputs("Invalid word argument\n", stderr);
            return EXIT_FAILURE;
        }

        words[i].data = argument;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        words[i].length = strlen(argument);
    }

    if (!shortlist_words(words, word_count, minimum_length,
                         &shortlisted, &shortlisted_count)) {
        free(words);
        fputs("Unable to shortlist words\n", stderr);
        return EXIT_FAILURE;
    }

    free(words);

    for (i = 0; i < shortlisted_count; ++i) {
        if (puts(shortlisted[i]) == EOF) {
            status = EXIT_FAILURE;
            break;
        }
    }

    if (status == EXIT_SUCCESS && fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free_word_list(shortlisted, shortlisted_count);
    return status;
}