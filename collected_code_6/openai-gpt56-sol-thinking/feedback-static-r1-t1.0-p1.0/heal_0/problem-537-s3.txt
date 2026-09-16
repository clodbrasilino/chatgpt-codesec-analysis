#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

WordSearchResult find_first_repeated_word(const char *string, char **repeated_word)
{
    const char *current;

    if (string == NULL || repeated_word == NULL) {
        return WORD_SEARCH_INVALID_ARGUMENT;
    }

    *repeated_word = NULL;
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
                memcmp(previous_start, current_start, current_length) == 0) {
                char *result;

                if (current_length == (size_t)-1) {
                    return WORD_SEARCH_OUT_OF_MEMORY;
                }

                result = malloc(current_length + 1U);
                if (result == NULL) {
                    return WORD_SEARCH_OUT_OF_MEMORY;
                }

                memcpy(result, current_start, current_length);
                result[current_length] = '\0';
                *repeated_word = result;
                return WORD_SEARCH_FOUND;
            }
        }
    }

    return WORD_SEARCH_NOT_FOUND;
}

int main(int argc, char *argv[])
{
    char *repeated_word = NULL;
    WordSearchResult result;
    int output_status;

    if (argc != 2) {
        output_status = fprintf(stderr, "Usage: %s \"string\"\n", argv[0]);
        return output_status < 0 ? EXIT_FAILURE : EXIT_FAILURE;
    }

    result = find_first_repeated_word(argv[1], &repeated_word);

    switch (result) {
        case WORD_SEARCH_FOUND:
            output_status = printf("%s\n", repeated_word);
            free(repeated_word);
            return output_status < 0 ? EXIT_FAILURE : EXIT_SUCCESS;

        case WORD_SEARCH_NOT_FOUND:
            output_status = printf("No repeated word\n");
            return output_status < 0 ? EXIT_FAILURE : EXIT_SUCCESS;

        case WORD_SEARCH_OUT_OF_MEMORY:
            output_status = fprintf(stderr, "Memory allocation failed\n");
            return output_status < 0 ? EXIT_FAILURE : EXIT_FAILURE;

        case WORD_SEARCH_INVALID_ARGUMENT:
        default:
            output_status = fprintf(stderr, "Invalid argument\n");
            return output_status < 0 ? EXIT_FAILURE : EXIT_FAILURE;
    }
}