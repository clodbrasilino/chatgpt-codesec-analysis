#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int remove_digits_from_strings(char *strings[], size_t count)
{
    size_t i;

    if (count > 0U && strings == NULL) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }
    }

    for (i = 0U; i < count; ++i) {
        size_t source = 0U;
        size_t destination = 0U;

        while (strings[i][source] != '\0') {
            char character = strings[i][source++];

            if (character < '0' || character > '9') {
                strings[i][destination++] = character;
            }
        }

        strings[i][destination] = '\0';
    }

    return 0;
}

int main(int argc, char *argv[])
{
    size_t count;
    size_t i;

    if (argc < 0 || argv == NULL) {
        return EXIT_FAILURE;
    }

    count = argc > 1 ? (size_t)(argc - 1) : 0U;

    if (remove_digits_from_strings(count > 0U ? &argv[1] : NULL, count) != 0) {
        return EXIT_FAILURE;
    }

    for (i = 1U; i < (size_t)argc; ++i) {
        if (fputs(argv[i], stdout) == EOF || fputc('\n', stdout) == EOF) {
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}