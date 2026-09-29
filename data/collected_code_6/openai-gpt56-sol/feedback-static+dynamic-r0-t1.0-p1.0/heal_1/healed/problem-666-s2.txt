#include <stdio.h>
#include <stdlib.h>

size_t count_character(const char *string, char character)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (*string == character) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(int argc, char *argv[])
{
    size_t count;

    if (argc != 3 || argv[0] == NULL || argv[1] == NULL || argv[2] == NULL ||
        argv[2][0] == '\0' || argv[2][1] != '\0') {
        fprintf(stderr, "Usage: %s <string> <character>\n",
                (argc > 0 && argv[0] != NULL) ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    count = count_character(argv[1], argv[2][0]);

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}