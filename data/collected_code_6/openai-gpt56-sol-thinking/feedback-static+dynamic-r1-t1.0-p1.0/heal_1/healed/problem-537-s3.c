#include <ctype.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    WORD_SEARCH_FOUND,
    WORD_SEARCH_NOT_FOUND,
    WORD_SEARCH_INVALID_ARGUMENT,
    WORD_SEARCH_OUT_OF_MEMORY
} WordSearchResult;

static int is_word_character(unsigned char character)
{
    return isalnum(character) != 0 || character == '_';
}

static int words_equal(const char *first, const char *second, size_t length)
{
    size_t index;

    for (index = 0; index < length; ++index) {
        if (first[index] != second[index]) {
            return 0;
        }
    }

    return 1;
}

WordSearchResult find_first_repeated_word(const char *string, char **repeated_word)
{
    const char *current;

    if (repeated_word == NULL) {
        return WORD_SEARCH_INVALID_ARGUMENT;
    }

    *repeated_word = NULL;

    if (string == NULL) {
        return WORD_SEARCH_INVALID_ARGUMENT;
    }

    current = string;

    while (*current != '\0') {
        const char *current_start;
        const char *previous;
        size_t current_length;

        while (*current != '\0' &&
               !is_word_character((unsigned char)*current)) {
            ++current;
        }

        if (*current == '\0') {
            break;
        }

        current_start = current;

        while (*current != '\0' &&
               is_word_character((unsigned char)*current)) {
            ++current;
        }

        current_length = (size_t)(current - current_start);
        previous = string;

        while (previous < current_start) {
            const char *previous_start;
            size_t previous_length;

            while (previous < current_start &&
                   !is_word_character((unsigned char)*previous)) {
                ++previous;
            }

            if (previous >= current_start) {
                break;
            }

            previous_start = previous;

            while (previous < current_start &&
                   is_word_character((unsigned char)*previous)) {
                ++previous;
            }

            previous_length = (size_t)(previous - previous_start);

            if (previous_length == current_length &&
                words_equal(previous_start, current_start, current_length)) {
                char *result;
                size_t index;

                if (current_length == SIZE_MAX) {
                    return WORD_SEARCH_OUT_OF_MEMORY;
                }

                result = malloc(current_length + 1U);
                if (result == NULL) {
                    return WORD_SEARCH_OUT_OF_MEMORY;
                }

                for (index = 0; index < current_length; ++index) {
                    result[index] = current_start[index];
                }

                result[current_length] = '\0';
                *repeated_word = result;
                return WORD_SEARCH_FOUND;
            }
        }
    }

    return WORD_SEARCH_NOT_FOUND;
}

int main(int argc, char **const argv)
{
    const char *program_name;
    char *repeated_word = NULL;
    WordSearchResult result;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    result = find_first_repeated_word(argv[1], &repeated_word);

    switch (result) {
        case WORD_SEARCH_FOUND:
            if (printf("%s\n", repeated_word) < 0) {
                free(repeated_word);
                return EXIT_FAILURE;
            }
            free(repeated_word);
            return EXIT_SUCCESS;

        case WORD_SEARCH_NOT_FOUND:
            return puts("No repeated word") == EOF
                       ? EXIT_FAILURE
                       : EXIT_SUCCESS;

        case WORD_SEARCH_OUT_OF_MEMORY:
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;

        case WORD_SEARCH_INVALID_ARGUMENT:
        default:
            fputs("Invalid argument\n", stderr);
            return EXIT_FAILURE;
    }
}