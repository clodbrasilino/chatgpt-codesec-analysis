#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        ++count;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}