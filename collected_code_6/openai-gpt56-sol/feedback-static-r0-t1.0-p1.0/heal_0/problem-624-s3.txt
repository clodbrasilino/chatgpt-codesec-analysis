#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int string_to_upper(char *string)
{
    unsigned char *current;

    if (string == NULL) {
        return -1;
    }

    current = (unsigned char *)string;

    while (*current != '\0') {
        *current = (unsigned char)toupper(*current);
        ++current;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = string_to_upper(argv[1]);
    if (result != 0) {
        fprintf(stderr, "Failed to convert the string.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", argv[1]) < 0) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}