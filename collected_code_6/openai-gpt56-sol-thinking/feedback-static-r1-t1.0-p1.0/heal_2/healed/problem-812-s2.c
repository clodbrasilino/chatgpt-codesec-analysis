#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH ((size_t)1048576)

static int is_word_character(char character)
{
    unsigned char value = (unsigned char)character;
    return isalnum(value) != 0 || value == (unsigned char)'_';
}

static int bounded_string_length(
    const char *string,
    size_t maximum_length,
    size_t *length)
{
    size_t index = 0;

    if (string == NULL || length == NULL) {
        return -1;
    }

    while (string[index] != '\0') {
        if (index == maximum_length) {
            return -1;
        }
        ++index;
    }

    *length = index;
    return 0;
}

static int abbreviate_road(
    const char *input,
    size_t input_length,
    char **output)
{
    size_t source = 0;
    size_t destination = 0;
    char *result;

    if (input == NULL || output == NULL || input_length == (size_t)-1) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    while (source < input_length) {
        if (input_length - source >= 4 &&
            input[source] == 'r' &&
            input[source + 1] == 'o' &&
            input[source + 2] == 'a' &&
            input[source + 3] == 'd' &&
            (source == 0 || !is_word_character(input[source - 1])) &&
            (input_length - source == 4 ||
             !is_word_character(input[source + 4]))) {
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
    const char *program_name;
    const char *input;
    size_t input_length;
    char *abbreviated = NULL;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];

    if (bounded_string_length(input, MAX_INPUT_LENGTH, &input_length) != 0) {
        fputs("Input is too long or invalid.\n", stderr);
        return EXIT_FAILURE;
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