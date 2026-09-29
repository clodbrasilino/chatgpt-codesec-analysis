#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *string_to_lower(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    const size_t length = strlen(input);

    if (length == SIZE_MAX) {
        return NULL;
    }

    char *output = malloc(length + 1U);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        output[i] = (char)tolower((unsigned char)input[i]);
    }

    output[length] = '\0';
    return output;
}

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *lowercase = string_to_lower(argv[1]);
    if (lowercase == NULL) {
        fputs("Failed to convert string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", lowercase) < 0) {
        free(lowercase);
        return EXIT_FAILURE;
    }

    free(lowercase);
    return EXIT_SUCCESS;
}