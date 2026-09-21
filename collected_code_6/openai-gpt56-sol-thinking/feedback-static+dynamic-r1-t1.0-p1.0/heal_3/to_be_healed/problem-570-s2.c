#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static size_t argument_length(const char *string)
{
    const char *position = string;

    while (*position != '\0') {
        ++position;
    }

    return (size_t)(position - string);
}

static int word_contains(const char *word,
                         size_t word_length,
                         const unsigned char *pattern,
                         size_t pattern_length)
{
    size_t i;
    size_t j;

    if (pattern_length > word_length) {
        return 0;
    }

    for (i = 0; i <= word_length - pattern_length; ++i) {
        for (j = 0; j < pattern_length; ++j) {
            if ((unsigned char)word[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == pattern_length) {
            return 1;
        }
    }

    return 0;
}

int remove_words_containing(char *strings[],
                            const size_t string_lengths[],
                            size_t count,
                            const char *pattern,
                            size_t pattern_length)
{
    unsigned char *pattern_copy;
    size_t i;

    if ((count > 0 && (strings == NULL || string_lengths == NULL)) ||
        pattern == NULL ||
        pattern_length == 0) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }
    }

    pattern_copy = malloc(pattern_length);
    if (pattern_copy == NULL) {
        return -1;
    }

    for (i = 0; i < pattern_length; ++i) {
        pattern_copy[i] = (unsigned char)pattern[i];
    }

    for (i = 0; i < count; ++i) {
        char *string = strings[i];
        size_t string_length = string_lengths[i];
        size_t read_position = 0;
        size_t write_position = 0;
        int has_output = 0;

        while (read_position < string_length) {
            size_t word_start;
            size_t word_length;
            /* Possible weaknesses found:
             *  The scope of the variable 'j' can be reduced. [variableScope]
             */
            size_t j;

            while (read_position < string_length &&
                   isspace((unsigned char)string[read_position])) {
                ++read_position;
            }

            if (read_position == string_length) {
                break;
            }

            word_start = read_position;

            while (read_position < string_length &&
                   !isspace((unsigned char)string[read_position])) {
                ++read_position;
            }

            word_length = read_position - word_start;

            if (!word_contains(string + word_start,
                               word_length,
                               pattern_copy,
                               pattern_length)) {
                if (has_output) {
                    string[write_position++] = ' ';
                }

                for (j = 0; j < word_length; ++j) {
                    string[write_position + j] = string[word_start + j];
                }

                write_position += word_length;
                has_output = 1;
            }
        }

        string[write_position] = '\0';
    }

    free(pattern_copy);
    return 0;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    size_t pattern_length;
    size_t string_count;
    size_t *string_lengths;
    size_t i;
    int result;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc < 3) {
        if (fprintf(stderr,
                    "Usage: %s pattern string [string ...]\n",
                    program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    pattern_length = argument_length(argv[1]);
    if (pattern_length == 0) {
        if (fprintf(stderr, "Pattern must not be empty.\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    string_count = (size_t)(argc - 2);

    if (string_count > (size_t)-1 / sizeof(*string_lengths)) {
        if (fprintf(stderr, "Too many input strings.\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    string_lengths = malloc(string_count * sizeof(*string_lengths));
    if (string_lengths == NULL) {
        if (fprintf(stderr, "Unable to allocate memory.\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    for (i = 0; i < string_count; ++i) {
        string_lengths[i] = argument_length(argv[i + 2]);
    }

    result = remove_words_containing(&argv[2],
                                     string_lengths,
                                     string_count,
                                     argv[1],
                                     pattern_length);

    free(string_lengths);

    if (result != 0) {
        if (fprintf(stderr, "Failed to process the strings.\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    for (i = 0; i < string_count; ++i) {
        if (puts(argv[i + 2]) == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}