#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *to_uppercase(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    size_t length = strlen(input);
    if (length == SIZE_MAX) {
        return NULL;
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
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *uppercase = to_uppercase(argv[1]);
    if (uppercase == NULL) {
        fputs("Failed to convert string\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(uppercase) == EOF) {
        free(uppercase);
        return EXIT_FAILURE;
    }

    free(uppercase);
    return EXIT_SUCCESS;
}