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
    char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)INPUT_CAPACITY, stdin) == NULL) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(input);
        return status;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (discard_line() != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", length) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}