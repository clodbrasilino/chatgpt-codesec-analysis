#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_lowercase(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (islower((unsigned char)*string) != 0) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    char buffer[4096];
    size_t count = 0;

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        count += count_lowercase(buffer);
    }

    if (ferror(stdin) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}