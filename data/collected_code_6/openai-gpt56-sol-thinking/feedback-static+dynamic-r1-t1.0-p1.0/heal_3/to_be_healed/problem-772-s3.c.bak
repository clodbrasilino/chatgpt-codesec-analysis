#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_words_with_length(char *string, size_t k)
{
    char *read;
    char *write;
    int has_word = 0;

    if (string == NULL) {
        return -1;
    }

    read = string;
    write = string;

    while (*read != '\0') {
        char *word_start;
        size_t word_length = 0;

        while (isspace((unsigned char)*read)) {
            ++read;
        }

        if (*read == '\0') {
            break;
        }

        word_start = read;

        while (*read != '\0' && !isspace((unsigned char)*read)) {
            ++read;
            ++word_length;
        }

        if (word_length != k) {
            if (has_word) {
                *write++ = ' ';
            }

            memmove(write, word_start, word_length);
            write += word_length;
            has_word = 1;
        }
    }

    *write = '\0';
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    const char *number;
    char *end;
    char *input;
    uintmax_t parsed;
    size_t total_length = 0;
    size_t position = 0;
    size_t k;
    int result;

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

    for (int i = 2; i < argc; ++i) {
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

    for (int i = 2; i < argc; ++i) {
        size_t argument_length = strlen(argv[i]);

        memcpy(input + position, argv[i], argument_length);
        position += argument_length;

        if (i + 1 < argc) {
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