#include <stdio.h>
#include <stdlib.h>

size_t string_length(const char *str)
{
    const char *current;

    if (str == NULL) {
        return 0;
    }

    current = str;

    while (*current != '\0') {
        ++current;
    }

    return (size_t)(current - str);
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("Failed to read input");
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    size_t length = string_length(input);

    if (length > 0 && input[length - 1] == '\n') {
        --length;
    }

    printf("%zu\n", length);

    return EXIT_SUCCESS;
}