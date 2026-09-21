#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int all_characters_are_unique(const char *string)
{
    unsigned char *seen;
    size_t seen_size;
    size_t index;

    if (string == NULL) {
        return -1;
    }

    seen_size = (size_t)UCHAR_MAX / (size_t)CHAR_BIT + 1U;
    seen = calloc(seen_size, sizeof(*seen));
    if (seen == NULL) {
        return -1;
    }

    for (index = 0U; string[index] != '\0'; ++index) {
        unsigned char character = (unsigned char)string[index];
        size_t byte_index = (size_t)character / (size_t)CHAR_BIT;
        unsigned int bit_offset =
            (unsigned int)((size_t)character % (size_t)CHAR_BIT);
        unsigned char mask =
            (unsigned char)(1U << bit_offset);

        if ((seen[byte_index] & mask) != 0U) {
            free(seen);
            return 0;
        }

        seen[byte_index] = (unsigned char)(seen[byte_index] | mask);
    }

    free(seen);
    return 1;
}

int main(int argc, char *argv[const])
{
    const char *program_name;
    int result;

    program_name =
        (argc > 0 && argv[0] != NULL) ? argv[0] : "program";

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    result = all_characters_are_unique(argv[1]);
    if (result < 0) {
        if (fputs("Unable to process the string.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (puts(result != 0 ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}