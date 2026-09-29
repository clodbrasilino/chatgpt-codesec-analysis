#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_digits(char *string)
{
    char *read_ptr = string;
    char *write_ptr = string;

    while (*read_ptr != '\0') {
        unsigned char character = (unsigned char)*read_ptr++;

        if (!isdigit(character)) {
            *write_ptr++ = (char)character;
        }
    }

    *write_ptr = '\0';
}

static void remove_digits_from_list(char *const strings[], size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        if (strings[i] != NULL) {
            remove_digits(strings[i]);
        }
    }
}

static void free_strings(char **strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s string [string ...]\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    size_t count = (size_t)argc - 1U;

    if (count > SIZE_MAX / sizeof(char *)) {
        fprintf(stderr, "Too many input strings\n");
        return EXIT_FAILURE;
    }

    char **strings = calloc(count, sizeof(*strings));

    if (strings == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        const char *source = argv[i + 1];

        if (source == NULL) {
            fprintf(stderr, "Invalid input string\n");
            free_strings(strings, count);
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(source);

        if (length == SIZE_MAX) {
            fprintf(stderr, "Input string is too long\n");
            free_strings(strings, count);
            return EXIT_FAILURE;
        }

        strings[i] = malloc(length + 1U);

        if (strings[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_strings(strings, count);
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(strings[i], source, length);
        strings[i][length] = '\0';
    }

    remove_digits_from_list(strings, count);

    for (size_t i = 0; i < count; ++i) {
        puts(strings[i]);
    }

    free_strings(strings, count);
    return EXIT_SUCCESS;
}