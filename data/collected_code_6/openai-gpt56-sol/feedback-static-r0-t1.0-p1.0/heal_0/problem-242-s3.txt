#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_characters(const char *string)
{
    return string == NULL ? 0U : strlen(string);
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    input[strcspn(input, "\n")] = '\0';

    if (printf("%zu\n", count_characters(input)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}