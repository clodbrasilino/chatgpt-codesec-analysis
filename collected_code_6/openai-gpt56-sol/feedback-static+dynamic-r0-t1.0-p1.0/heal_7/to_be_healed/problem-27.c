#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_digits(char *string)
{
    char *read_ptr = string;
    char *write_ptr = string;

    while (*read_ptr != '\0') {
        const unsigned char character = (unsigned char)*read_ptr;

        if (!isdigit(character)) {
            *write_ptr++ = *read_ptr;
        }

        ++read_ptr;
    }

    *write_ptr = '\0';
}

static void remove_digits_from_list(char *strings[], size_t count)
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

static void free_strings(char *strings[], size_t count)
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
    const char *const *arguments = (const char *const *)argv;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s string [string ...]\n",
                argc > 0 && arguments[0] != NULL
                    ? arguments[0]
                    : "program");
        return EXIT_FAILURE;
    }

    const size_t count = (size_t)(argc - 1);
    char **strings = calloc(count, sizeof(*strings));

    if (strings == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        const char *argument = arguments[i + 1];

        if (argument == NULL) {
            fputs("Invalid input string\n", stderr);
            free_strings(strings, count);
            return EXIT_FAILURE;
        }

        const size_t length = strlen(argument);

        if (length == SIZE_MAX) {
            fputs("Input string is too long\n", stderr);
            free_strings(strings, count);
            return EXIT_FAILURE;
        }

        strings[i] = malloc(length + 1);

        if (strings[i] == NULL) {
            fputs("Memory allocation failed\n", stderr);
            free_strings(strings, count);
            return EXIT_FAILURE;
        }

        memcpy(strings[i], argument, length + 1);
    }

    remove_digits_from_list(strings, count);

    for (size_t i = 0; i < count; ++i) {
        puts(strings[i]);
    }

    free_strings(strings, count);
    return EXIT_SUCCESS;
}