#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int all_characters_are_unique(const char *string)
{
    unsigned char seen[UCHAR_MAX / CHAR_BIT + 1U] = {0};
    size_t index;

    if (string == NULL) {
        return -1;
    }

    for (index = 0; string[index] != '\0'; ++index) {
        unsigned char character = (unsigned char)string[index];
        size_t byte_index = character / CHAR_BIT;
        unsigned int bit_mask = 1U << (character % CHAR_BIT);

        if ((seen[byte_index] & bit_mask) != 0U) {
            return 0;
        }

        seen[byte_index] =
            (unsigned char)(seen[byte_index] | bit_mask);
    }

    return 1;
}

int main(int argc, char *const argv[])
{
    int result;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

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