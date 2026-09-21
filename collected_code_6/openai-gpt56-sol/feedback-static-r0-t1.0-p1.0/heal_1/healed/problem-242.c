#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 0;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (count == SIZE_MAX) {
            fprintf(stderr, "Input is too long.\n");
            return EXIT_FAILURE;
        }
        ++count;
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (character == EOF && count == 0) {
        return EXIT_SUCCESS;
    }

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}