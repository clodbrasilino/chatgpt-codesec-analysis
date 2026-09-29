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
    if (argc != 3) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return 1;
    }

    const char *first = argv[1];
    const char *second = argv[2];

    if (first == NULL || second == NULL) {
        fputs("Invalid null argument.\n", stderr);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t first_length = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t second_length = strlen(second);

    if (are_permutations(first, first_length, second, second_length)) {
        puts("The strings are permutations of each other.");
    } else {
        puts("The strings are not permutations of each other.");
    }

    return 0;
}