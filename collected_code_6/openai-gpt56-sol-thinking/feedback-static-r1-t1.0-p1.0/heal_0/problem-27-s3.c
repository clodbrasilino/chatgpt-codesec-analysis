#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int remove_digits_from_strings(char *const strings[], size_t count)
{
    size_t i;

    if (count > 0 && strings == NULL) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return 0;
        }
    }

    for (i = 0; i < count; ++i) {
        char *read_ptr = strings[i];
        char *write_ptr = strings[i];

        while (*read_ptr != '\0') {
            if (!isdigit((unsigned char)*read_ptr)) {
                *write_ptr++ = *read_ptr;
            }
            ++read_ptr;
        }

        *write_ptr = '\0';
    }

    return 1;
}

int main(int argc, char *argv[])
{
    size_t count;
    size_t i;

    if (argc < 1 || argv == NULL) {
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (!remove_digits_from_strings(argv + 1, count)) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (puts(argv[i + 1]) == EOF) {
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}