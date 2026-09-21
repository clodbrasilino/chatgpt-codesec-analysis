#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_word_character(char character)
{
    unsigned char value = (unsigned char)character;
    return isalnum(value) != 0 || value == '_';
}

static int abbreviate_road(const char *input, size_t input_length, char **output)
{
    size_t source = 0;
    size_t destination = 0;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    if (input_length == SIZE_MAX) {
        return -1;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    while (source < input_length) {
        size_t remaining = input_length - source;

        if (remaining >= 4 &&
            input[source] == 'r' &&
            input[source + 1] == 'o' &&
            input[source + 2] == 'a' &&
            input[source + 3] == 'd' &&
            (source == 0 || !is_word_character(input[source - 1])) &&
            (remaining == 4 || !is_word_character(input[source + 4]))) {
            result[destination++] = 'r';
            result[destination++] = 'd';
            result[destination++] = '.';
            source += 4;
        } else {
            result[destination++] = input[source++];
        }
    }

    result[destination] = '\0';
    *output = result;
    return 0;
}

int main(int argc, char *argv[])
{
    const char *input;
    const char *program_name;
    size_t input_length = 0;
    char *abbreviated = NULL;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];

    while (input[input_length] != '\0') {
        if (input_length == SIZE_MAX - 1) {
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    if (abbreviate_road(input, input_length, &abbreviated) != 0) {
        fputs("Unable to abbreviate the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(abbreviated) == EOF) {
        free(abbreviated);
        return EXIT_FAILURE;
    }

    free(abbreviated);
    return EXIT_SUCCESS;
}