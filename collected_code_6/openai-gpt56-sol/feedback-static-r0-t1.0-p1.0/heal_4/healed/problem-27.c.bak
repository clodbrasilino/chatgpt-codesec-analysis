#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_digits(char *string)
{
    char *read_ptr = string;
    char *write_ptr = string;

    while (*read_ptr != '\0') {
        unsigned char character = (unsigned char)*read_ptr;

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

int main(int argc, char *argv[])
{
    const char *program_name = argc > 0 && argv[0] != NULL
                                   ? argv[0]
                                   : "program";

    if (argc < 2) {
        fprintf(stderr, "Usage: %s string [string ...]\n", program_name);
        return EXIT_FAILURE;
    }

    const size_t count = (size_t)(argc - 1);
    char **strings = calloc(count, sizeof(*strings));

    if (strings == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        const char *input = argv[i + 1];
        const size_t length = strlen(input);

        strings[i] = malloc(length + 1);

        if (strings[i] == NULL) {
            fputs("Memory allocation failed\n", stderr);
            free_strings(strings, i);
            return EXIT_FAILURE;
        }

        memcpy(strings[i], input, length + 1);
    }

    remove_digits_from_list(strings, count);

    for (size_t i = 0; i < count; ++i) {
        puts(strings[i]);
    }

    free_strings(strings, count);
    return EXIT_SUCCESS;
}