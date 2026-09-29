#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool are_permutations(const char *first, size_t first_length,
                             const char *second, size_t second_length)
{
    size_t counts[256] = {0};

    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    for (size_t i = 0; i < first_length; ++i) {
        ++counts[(unsigned char)first[i]];
    }

    for (size_t i = 0; i < second_length; ++i) {
        unsigned char character = (unsigned char)second[i];

        if (counts[character] == 0) {
            return false;
        }

        --counts[character];
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return 1;
    }

    size_t first_length = 0;
    size_t second_length = 0;

    while (argv[1][first_length] != '\0') {
        ++first_length;
    }

    while (argv[2][second_length] != '\0') {
        ++second_length;
    }

    if (are_permutations(argv[1], first_length, argv[2], second_length)) {
        puts("The strings are permutations of each other.");
    } else {
        puts("The strings are not permutations of each other.");
    }

    return 0;
}