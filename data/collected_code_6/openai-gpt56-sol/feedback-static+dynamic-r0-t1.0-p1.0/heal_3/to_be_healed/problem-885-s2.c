#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'UCHAR_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static bool are_isomorphic(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t first_length = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    /* Possible weaknesses found:
     *  'UCHAR_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'UCHAR_MAX'
     */
    bool first_mapped[UCHAR_MAX + 1] = {false};
    /* Possible weaknesses found:
     *  use of undeclared identifier 'UCHAR_MAX'
     */
    bool second_mapped[UCHAR_MAX + 1] = {false};
    /* Possible weaknesses found:
     *  use of undeclared identifier 'UCHAR_MAX'
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char first_to_second[UCHAR_MAX + 1] = {0};

    for (size_t i = 0; i < first_length; ++i) {
        unsigned char first_char = (unsigned char)first[i];
        unsigned char second_char = (unsigned char)second[i];

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

    puts(are_isomorphic(argv[1], argv[2])
             ? "The strings are isomorphic."
             : "The strings are not isomorphic.");

    return 0;
}