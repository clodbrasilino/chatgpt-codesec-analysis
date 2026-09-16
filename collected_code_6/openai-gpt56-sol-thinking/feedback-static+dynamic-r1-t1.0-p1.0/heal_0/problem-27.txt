#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int remove_digits_from_strings(char *const strings[], size_t count)
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
        char *source = strings[i];
        char *destination = strings[i];

        while (*source != '\0') {
            unsigned char character = (unsigned char)*source++;

            if (isdigit(character) == 0) {
                *destination++ = (char)character;
            }
        }

        *destination = '\0';
    }

    return 0;
}

int main(int argc, char *argv[])
{
    size_t i;
    size_t count;

    if (argc <= 1) {
        return EXIT_SUCCESS;
    }

    count = (size_t)(argc - 1);

    if (remove_digits_from_strings(&argv[1], count) != 0) {
        (void)fputs("Failed to process the strings.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 1U; i < (size_t)argc; ++i) {
        if (printf("%s\n", argv[i]) < 0) {
            (void)fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        (void)fputs("Failed to flush output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}