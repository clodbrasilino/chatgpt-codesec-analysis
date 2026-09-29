#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

bool strings_are_isomorphic(const char *first, const char *second)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char first_to_second[UCHAR_MAX + 1] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char second_to_first[UCHAR_MAX + 1] = {0};

    if (first == NULL || second == NULL) {
        return false;
    }

    while (*first != '\0' && *second != '\0') {
        unsigned char first_char = (unsigned char)*first;
        unsigned char second_char = (unsigned char)*second;

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char *result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
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