#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_CAPACITY 1024U

static int discard_line(void)
{
    int character;

    do {
        character = getchar();
    } while (character != '\n' && character != EOF);

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char input[INPUT_CAPACITY];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (discard_line() != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}