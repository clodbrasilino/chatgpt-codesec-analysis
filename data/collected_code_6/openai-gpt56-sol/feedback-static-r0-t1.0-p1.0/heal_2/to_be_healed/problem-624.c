#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *to_uppercase(const char *input, size_t input_size)
{
    if (input == NULL) {
        return NULL;
    }

    const char *terminator = memchr(input, '\0', input_size);
    if (terminator == NULL) {
        return NULL;
    }

    size_t length = (size_t)(terminator - input);
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
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *uppercase = to_uppercase(argv[1], strlen(argv[1]) + 1);
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