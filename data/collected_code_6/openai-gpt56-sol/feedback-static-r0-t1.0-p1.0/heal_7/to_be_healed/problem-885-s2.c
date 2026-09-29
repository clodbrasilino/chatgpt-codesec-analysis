#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool are_isomorphic(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    bool mapped[UCHAR_MAX + 1] = { false };
    bool used[UCHAR_MAX + 1] = { false };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char mapping[UCHAR_MAX + 1] = { 0 };

    const unsigned char *left = (const unsigned char *)first;
    const unsigned char *right = (const unsigned char *)second;

    while (*left != '\0' && *right != '\0') {
        unsigned char left_char = *left;
        unsigned char right_char = *right;

        if (mapped[left_char]) {
            if (mapping[left_char] != right_char) {
                return false;
            }
        } else {
            if (used[right_char]) {
                return false;
            }

            mapping[left_char] = right_char;
            mapped[left_char] = true;
            used[right_char] = true;
        }

        ++left;
        ++right;
    }

    return *left == *right;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    const char *program_name = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return EXIT_FAILURE;
    }

    puts(are_isomorphic(argv[1], argv[2])
             ? "The strings are isomorphic."
             : "The strings are not isomorphic.");

    return EXIT_SUCCESS;
}