#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *to_uppercase(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    size_t length = 0;

    while (input[length] != '\0') {
        if (length == SIZE_MAX - 1) {
            return NULL;
        }
        ++length;
    }

    char *output = malloc(length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        output[i] = (char)toupper((unsigned char)input[i]);
    }

    output[length] = '\0';
    return output;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        const char *program = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    char *uppercase = to_uppercase(argv[1]);
    if (uppercase == NULL) {
        fputs("Failed to convert string\n", stderr);
        return EXIT_FAILURE;
    }

    const int result = puts(uppercase);
    free(uppercase);

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}