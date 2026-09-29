#include <stdio.h>
#include <stdlib.h>

size_t count_characters(const char *string, size_t capacity)
{
    size_t length = 0;

    if (string == NULL) {
        return 0;
    }

    while (length < capacity && string[length] != '\0') {
        ++length;
    }

    return length;
}

int main(void)
{
    char input[1024];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    length = count_characters(input, sizeof input);

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else if (length == sizeof input - 1) {
        int character;

        while ((character = getchar()) != '\n' && character != EOF) {
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (printf("%zu\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}