#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_uppercase(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (isupper((unsigned char)*string) != 0) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    size_t count = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (isupper((unsigned char)ch) != 0) {
            ++count;
        }
    }

    if (ferror(stdin) != 0) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}