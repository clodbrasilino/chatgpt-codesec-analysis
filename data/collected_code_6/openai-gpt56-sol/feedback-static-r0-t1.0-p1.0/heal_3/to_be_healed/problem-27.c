#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_digits(char *string)
{
    if (string == NULL) {
        return;
    }

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
        remove_digits(strings[i]);
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

static char *duplicate_string(const char *source)
{
    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    char *copy = malloc(length + 1U);

    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1U);
    return copy;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s string [string ...]\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    const size_t count = (size_t)argc - 1U;
    char **strings = calloc(count, sizeof(*strings));

    if (strings == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        strings[i] = duplicate_string(argv[i + 1]);

        if (strings[i] == NULL) {
            fputs("Memory allocation failed or invalid input\n", stderr);
            free_strings(strings, count);
            return EXIT_FAILURE;
        }
    }

    remove_digits_from_list(strings, count);

    for (size_t i = 0; i < count; ++i) {
        if (puts(strings[i]) == EOF) {
            fputs("Output error\n", stderr);
            free_strings(strings, count);
            return EXIT_FAILURE;
        }
    }

    free_strings(strings, count);
    return EXIT_SUCCESS;
}