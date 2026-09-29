#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool are_isomorphic(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    bool first_mapped[UCHAR_MAX + 1] = {false};
    bool second_mapped[UCHAR_MAX + 1] = {false};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char first_to_second[UCHAR_MAX + 1] = {0};

    for (;;) {
        unsigned char first_char = (unsigned char)*first;
        unsigned char second_char = (unsigned char)*second;

        if (first_char == '\0' || second_char == '\0') {
            return first_char == second_char;
        }

        if (first_mapped[first_char]) {
            if (first_to_second[first_char] != second_char) {
                return false;
            }
        } else {
            if (second_mapped[second_char]) {
                return false;
            }

            first_to_second[first_char] = second_char;
            first_mapped[first_char] = true;
            second_mapped[second_char] = true;
        }

        ++first;
        ++second;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return 1;
    }

    puts(are_isomorphic(argv[1], argv[2])
             ? "The strings are isomorphic."
             : "The strings are not isomorphic.");

    return 0;
}