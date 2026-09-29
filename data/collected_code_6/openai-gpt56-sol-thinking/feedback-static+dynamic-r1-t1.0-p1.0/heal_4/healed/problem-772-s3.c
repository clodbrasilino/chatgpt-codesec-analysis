#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_words_with_length(char *string, size_t capacity, size_t k)
{
    size_t input_length = 0;
    size_t source = 0;
    size_t destination = 0;
    int has_word = 0;

    if (string == NULL || capacity == 0) {
        return -1;
    }

    while (input_length < capacity && string[input_length] != '\0') {
        ++input_length;
    }

    if (input_length == capacity) {
        return -1;
    }

    while (source < input_length) {
        size_t word_start;
        size_t word_length;

        while (source < input_length &&
               isspace((unsigned char)string[source])) {
            ++source;
        }

        if (source == input_length) {
            break;
        }

        word_start = source;

        while (source < input_length &&
               !isspace((unsigned char)string[source])) {
            ++source;
        }

        word_length = source - word_start;

        if (word_length == k) {
            continue;
        }

        if (has_word) {
            if (destination >= capacity - 1) {
                return -1;
            }

            string[destination++] = ' ';
        }

        if (word_length > capacity - 1 - destination) {
            return -1;
        }

        memmove(string + destination, string + word_start, word_length);
        destination += word_length;
        has_word = 1;
    }

    string[destination] = '\0';
    return 0;
}

int main(int argc, char **const argv)
{
    const char *number;
    char *end;
    uintmax_t parsed;
    size_t total_length = 0;
    size_t position = 0;
    size_t k;
    char *input;
    int result;
    int i;

    if (argc < 3) {
        fputs("Usage: program k string\n", stderr);
        return EXIT_FAILURE;
    }

    number = argv[1];

    while (isspace((unsigned char)*number)) {
        ++number;
    }

    if (*number == '\0' || *number == '-') {
        fputs("Invalid word length\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(number, &end, 10);

    if (errno == ERANGE ||
        end == number ||
        *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        fputs("Invalid word length\n", stderr);
        return EXIT_FAILURE;
    }

    k = (size_t)parsed;

    for (i = 2; i < argc; ++i) {
        size_t argument_length = strlen(argv[i]);

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
        size_t argument_length = strlen(argv[i]);

        memcpy(input + position, argv[i], argument_length);
        position += argument_length;

        if (i + 1 < argc) {
            input[position++] = ' ';
        }
    }

    input[position] = '\0';

    if (remove_words_with_length(input, total_length + 1, k) != 0) {
        free(input);
        fputs("Failed to process the string\n", stderr);
        return EXIT_FAILURE;
    }

    result = printf("%s\n", input);
    free(input);

    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}