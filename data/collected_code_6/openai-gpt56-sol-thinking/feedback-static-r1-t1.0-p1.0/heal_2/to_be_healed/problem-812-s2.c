#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_word_character(char character)
{
    unsigned char value = (unsigned char)character;
    return isalnum(value) != 0 || value == (unsigned char)'_';
}

static int abbreviate_road(
    const char *input,
    size_t input_length,
    char **output)
{
    size_t source = 0;
    size_t destination = 0;
    char *result;

    if (output == NULL) {
        return -1;
    }

    *output = NULL;

    if (input == NULL || input_length == (size_t)-1) {
        return -1;
    }

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

int main(int argc, char *const argv[])
{
    const char *input;
    size_t input_length;
    char *abbreviated = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

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