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

static char *duplicate_string(const char *source)
{
    if (source == NULL) {
        return NULL;
    }

    size_t length = strlen(source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    char *copy = malloc(length + 1);

    if (copy == NULL) {
        return NULL;
    }

    snprintf(copy, length + 1, "%s", source);
    return copy;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argv == NULL) {
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
        if (argv[i + 1] == NULL) {
            fputs("Invalid input string\n", stderr);
            free_string_list(strings, initialized);
            return EXIT_FAILURE;
        }

        strings[i] = duplicate_string(argv[i + 1]);

        if (strings[i] == NULL) {
            fputs("Memory allocation failed\n", stderr);
            free_string_list(strings, initialized);
            return EXIT_FAILURE;
        }

        ++initialized;
    }

    for (size_t i = 0; i < count; ++i) {
        remove_digits(strings[i]);

        if (puts(strings[i]) == EOF) {
            fputs("Output failed\n", stderr);
            free_string_list(strings, count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(strings, count);
    return EXIT_SUCCESS;
}