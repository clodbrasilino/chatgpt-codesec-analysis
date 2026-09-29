#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (argc != 3 || strlen(argv[2]) != 1U) {
        fprintf(stderr, "Usage: %s <string> <character>\n", argv[0]);
        return EXIT_FAILURE;
    }

    count = count_character(argv[1], argv[2][0]);
    printf("%zu\n", count);

    return EXIT_SUCCESS;
}