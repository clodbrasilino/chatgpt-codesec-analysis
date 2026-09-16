#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

bool strings_are_isomorphic(const char *first, const char *second)
{
    unsigned char first_to_second[UCHAR_MAX + 1] = {0};
    unsigned char second_to_first[UCHAR_MAX + 1] = {0};

    if (first == NULL || second == NULL) {
        return false;
    }

    while (*first != '\0' && *second != '\0') {
        const unsigned char first_char = (unsigned char)*first;
        const unsigned char second_char = (unsigned char)*second;

        if (first_to_second[first_char] == 0 &&
            second_to_first[second_char] == 0) {
            first_to_second[first_char] = second_char;
            second_to_first[second_char] = first_char;
        } else if (first_to_second[first_char] != second_char ||
                   second_to_first[second_char] != first_char) {
            return false;
        }

        ++first;
        ++second;
    }

    return *first == '\0' && *second == '\0';
}

int main(int argc, char *const argv[])
{
    const char *program_name;
    const char *result;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return EXIT_FAILURE;
    }

    result = strings_are_isomorphic(argv[1], argv[2])
                 ? "The strings are isomorphic.\n"
                 : "The strings are not isomorphic.\n";

    if (fputs(result, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}