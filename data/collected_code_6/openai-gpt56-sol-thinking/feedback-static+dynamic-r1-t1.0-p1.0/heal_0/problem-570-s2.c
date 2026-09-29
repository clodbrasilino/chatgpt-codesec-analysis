#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int word_contains(const char *word, size_t word_length,
                         const char *pattern, size_t pattern_length)
{
    size_t i;

    if (pattern_length > word_length) {
        return 0;
    }

    for (i = 0; i <= word_length - pattern_length; ++i) {
        if (memcmp(word + i, pattern, pattern_length) == 0) {
            return 1;
        }
    }

    return 0;
}

int remove_words_containing(char *strings[], size_t count,
                            const char *pattern)
{
    size_t pattern_length;
    size_t i;

    if ((count > 0 && strings == NULL) ||
        pattern == NULL ||
        pattern[0] == '\0') {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }
    }

    pattern_length = strlen(pattern);

    for (i = 0; i < count; ++i) {
        char *read_position = strings[i];
        char *write_position = strings[i];
        int has_output = 0;

        while (*read_position != '\0') {
            char *word;
            size_t word_length;

            while (*read_position != '\0' &&
                   isspace((unsigned char)*read_position)) {
                ++read_position;
            }

            if (*read_position == '\0') {
                break;
            }

            word = read_position;

            while (*read_position != '\0' &&
                   !isspace((unsigned char)*read_position)) {
                ++read_position;
            }

            word_length = (size_t)(read_position - word);

            if (!word_contains(word, word_length, pattern, pattern_length)) {
                if (has_output) {
                    *write_position++ = ' ';
                }

                memmove(write_position, word, word_length);
                write_position += word_length;
                has_output = 1;
            }
        }

        *write_position = '\0';
    }

    return 0;
}

int main(int argc, char *argv[])
{
    size_t string_count;
    size_t i;

    if (argc < 3) {
        if (fprintf(stderr, "Usage: %s pattern string [string ...]\n",
                    argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        if (fprintf(stderr, "Pattern must not be empty.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    string_count = (size_t)(argc - 2);

    if (remove_words_containing(&argv[2], string_count, argv[1]) != 0) {
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