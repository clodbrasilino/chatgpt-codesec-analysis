#include <ctype.h>
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

static void free_string_list(char **strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s string [string ...]\n", program);
        return EXIT_FAILURE;
    }

    size_t count = (size_t)argc - 1;

    if (count > SIZE_MAX / sizeof(char *)) {
        fputs("Too many input strings\n", stderr);
        return EXIT_FAILURE;
    }

    char **strings = calloc(count, sizeof(*strings));

    if (strings == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    size_t initialized = 0;

    for (size_t i = 0; i < count; ++i) {
        const char *source = argv[i + 1];

        if (source == NULL) {
            fputs("Invalid input string\n", stderr);
            free_string_list(strings, initialized);
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(source);

        if (length == SIZE_MAX) {
            fputs("Input string is too long\n", stderr);
            free_string_list(strings, initialized);
            return EXIT_FAILURE;
        }

        strings[i] = malloc(length + 1);

        if (strings[i] == NULL) {
            fputs("Memory allocation failed\n", stderr);
            free_string_list(strings, initialized);
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(strings[i], source, length);
        strings[i][length] = '\0';
        ++initialized;
    }

    for (size_t i = 0; i < count; ++i) {
        remove_digits(strings[i]);
        puts(strings[i]);
    }

    free_string_list(strings, count);
    return EXIT_SUCCESS;
}