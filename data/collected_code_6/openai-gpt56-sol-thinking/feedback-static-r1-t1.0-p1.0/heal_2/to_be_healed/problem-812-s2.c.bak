#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_word_character(char c)
{
    const unsigned char value = (unsigned char)c;

    return isalnum(value) || value == '_';
}

static int abbreviate_road(const char *input, char **output)
{
    size_t input_length;
    size_t source = 0;
    size_t destination = 0;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    input_length = strlen(input);
    result = malloc(input_length + 1);

    if (result == NULL) {
        return -1;
    }

    while (source < input_length) {
        if (source + 4 <= input_length &&
            memcmp(input + source, "road", 4) == 0 &&
            (source == 0 || !is_word_character(input[source - 1])) &&
            (source + 4 == input_length ||
             !is_word_character(input[source + 4]))) {
            memcpy(result + destination, "rd.", 3);
            source += 4;
            destination += 3;
        } else {
            result[destination++] = input[source++];
        }
    }

    result[destination] = '\0';
    *output = result;

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    char *abbreviated = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (abbreviate_road(argv[1], &abbreviated) != 0) {
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