#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_word_character(char c)
{
    unsigned char value = (unsigned char)c;
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
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
int main(int argc, char *argv[])
{
    char *abbreviated;

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