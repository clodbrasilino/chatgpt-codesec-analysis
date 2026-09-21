#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool all_characters_unique(const char *string)
{
    if (string == NULL) {
        return false;
    }

    for (const unsigned char *current = (const unsigned char *)string;
         *current != '\0';
         ++current) {
        for (const unsigned char *remaining = current + 1;
             *remaining != '\0';
             ++remaining) {
            if (*current == *remaining) {
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (printf("%s\n",
               all_characters_unique(argv[1]) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}