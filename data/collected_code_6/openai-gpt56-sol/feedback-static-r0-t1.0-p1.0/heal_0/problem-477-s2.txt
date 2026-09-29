#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int string_to_lower(char *string)
{
    unsigned char *current;

    if (string == NULL) {
        return -1;
    }

    current = (unsigned char *)string;

    while (*current != '\0') {
        *current = (unsigned char)tolower(*current);
        ++current;
    }

    return 0;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (string_to_lower(input) != 0) {
        return EXIT_FAILURE;
    }

    if (fputs(input, stdout) == EOF) {
        perror("fputs");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}