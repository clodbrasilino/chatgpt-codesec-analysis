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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char *const *arguments = (const char *const *)argv;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n",
                argc > 0 && arguments[0] != NULL ? arguments[0] : "program");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t first_length = strlen(arguments[1]);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t second_length = strlen(arguments[2]);

    if (are_permutations(arguments[1], first_length,
                         arguments[2], second_length)) {
        puts("The strings are permutations of each other.");
    } else {
        puts("The strings are not permutations of each other.");
    }

    return 0;
}