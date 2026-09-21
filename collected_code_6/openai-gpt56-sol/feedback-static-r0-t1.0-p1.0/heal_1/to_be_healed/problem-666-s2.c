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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (argc != 3 || strlen(argv[2]) != 1U) {
        fprintf(stderr, "Usage: %s <string> <character>\n", argv[0]);
        return EXIT_FAILURE;
    }

    count = count_character(argv[1], argv[2][0]);
    printf("%zu\n", count);

    return EXIT_SUCCESS;
}