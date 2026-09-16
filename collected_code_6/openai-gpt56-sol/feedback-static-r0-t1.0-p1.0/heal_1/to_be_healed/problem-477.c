#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_to_lower(const char *input)
{
    size_t length;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    length = strlen(input);

    if (length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(length + 1U);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        output[i] = (char)tolower((unsigned char)input[i]);
    }

    output[length] = '\0';
    return output;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *lowercase;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    lowercase = string_to_lower(argv[1]);
    if (lowercase == NULL) {
        fprintf(stderr, "Failed to convert string.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", lowercase) < 0) {
        free(lowercase);
        return EXIT_FAILURE;
    }

    free(lowercase);
    return EXIT_SUCCESS;
}