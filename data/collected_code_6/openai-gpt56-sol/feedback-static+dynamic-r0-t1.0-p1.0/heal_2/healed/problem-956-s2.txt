#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static int split_at_uppercase(const char *input)
{
    const unsigned char *start;
    const unsigned char *current;
    size_t length;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    length = strnlen(input, SIZE_MAX);
    if (length == SIZE_MAX) {
        return EXIT_FAILURE;
    }

    start = (const unsigned char *)input;
    current = start;

    while (*current != '\0') {
        if (current != start && isupper(*current)) {
            if (fwrite(start, 1, (size_t)(current - start), stdout) !=
                    (size_t)(current - start) ||
                fputc('\n', stdout) == EOF) {
                return EXIT_FAILURE;
            }
            start = current;
        }
        ++current;
    }

    if (current != start) {
        if (fwrite(start, 1, (size_t)(current - start), stdout) !=
                (size_t)(current - start) ||
            fputc('\n', stdout) == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    const char *program_name =
        (argc > 0 && argv != NULL && argv[0] != NULL) ? argv[0] : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return split_at_uppercase(argv[1]);
}