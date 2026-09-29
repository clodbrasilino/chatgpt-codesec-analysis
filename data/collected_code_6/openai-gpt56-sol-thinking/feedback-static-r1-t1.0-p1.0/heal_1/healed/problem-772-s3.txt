#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int get_string_length(const char *string, size_t *length)
{
    size_t count = 0;

    if (string == NULL || length == NULL) {
        return -1;
    }

    while (string[count] != '\0') {
        ++count;
    }

    *length = count;
    return 0;
}

int remove_words_with_length(char *string, size_t k)
{
    size_t source = 0;
    size_t destination = 0;
    size_t string_length;
    int has_word = 0;

    if (get_string_length(string, &string_length) != 0) {
        return -1;
    }

    while (source < string_length) {
        size_t word_start;
        size_t word_length;
        size_t i;

        while (source < string_length &&
               isspace((unsigned char)string[source])) {
            ++source;
        }

        if (source == string_length) {
            break;
        }

        word_start = source;

        while (source < string_length &&
               !isspace((unsigned char)string[source])) {
            ++source;
        }

        word_length = source - word_start;

        if (word_length != k) {
            if (has_word) {
                if (destination >= string_length) {
                    return -1;
                }

                string[destination++] = ' ';
            }

            if (word_length > string_length - destination) {
                return -1;
            }

            for (i = 0; i < word_length; ++i) {
                string[destination + i] = string[word_start + i];
            }

            destination += word_length;
            has_word = 1;
        }
    }

    string[destination] = '\0';
    return 0;
}

static int parse_word_length(const char *text, size_t *value)
{
    const char *number;
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL) {
        return -1;
    }

    number = text;

    while (isspace((unsigned char)*number)) {
        ++number;
    }

    if (*number == '\0' || *number == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(number, &end, 10);

    if (errno == ERANGE ||
        end == number ||
        *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

int main(int argc, char *argv[])
{
    char *input;
    size_t total_length = 0;
    size_t position = 0;
    size_t k;
    int i;
    int result;

    if (argc < 3) {
        fputs("Usage: program k string\n", stderr);
        return EXIT_FAILURE;
    }

    if (parse_word_length(argv[1], &k) != 0) {
        fputs("Invalid word length\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 2; i < argc; ++i) {
        size_t argument_length;

        if (get_string_length(argv[i], &argument_length) != 0) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        if (argument_length > SIZE_MAX - total_length) {
            fputs("Input is too large\n", stderr);
            return EXIT_FAILURE;
        }

        total_length += argument_length;

        if (i + 1 < argc) {
            if (total_length == SIZE_MAX) {
                fputs("Input is too large\n", stderr);
                return EXIT_FAILURE;
            }

            ++total_length;
        }
    }

    if (total_length == SIZE_MAX) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    input = malloc(total_length + 1);
    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 2; i < argc; ++i) {
        size_t argument_length;
        size_t j;

        if (get_string_length(argv[i], &argument_length) != 0 ||
            argument_length > total_length - position) {
            free(input);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        for (j = 0; j < argument_length; ++j) {
            input[position++] = argv[i][j];
        }

        if (i + 1 < argc) {
            if (position >= total_length) {
                free(input);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            input[position++] = ' ';
        }
    }

    input[position] = '\0';

    if (remove_words_with_length(input, k) != 0) {
        free(input);
        fputs("Failed to process the string\n", stderr);
        return EXIT_FAILURE;
    }

    result = printf("%s\n", input);
    free(input);

    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}