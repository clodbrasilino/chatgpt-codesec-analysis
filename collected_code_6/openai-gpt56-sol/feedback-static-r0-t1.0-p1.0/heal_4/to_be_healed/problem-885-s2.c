#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UCHAR_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static bool are_isomorphic(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'UCHAR_MAX'
     *  'UCHAR_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    size_t alphabet_size = (size_t)UCHAR_MAX + 1U;
    unsigned char *first_to_second = calloc(alphabet_size, sizeof(*first_to_second));
    bool *first_has_mapping = calloc(alphabet_size, sizeof(*first_has_mapping));
    bool *second_used = calloc(alphabet_size, sizeof(*second_used));

    if (first_to_second == NULL || first_has_mapping == NULL || second_used == NULL) {
        free(first_to_second);
        free(first_has_mapping);
        free(second_used);
        return false;
    }

    const unsigned char *left = (const unsigned char *)first;
    const unsigned char *right = (const unsigned char *)second;
    bool result = true;

    while (*left != '\0' && *right != '\0') {
        unsigned char left_char = *left++;
        unsigned char right_char = *right++;

        if (first_has_mapping[left_char]) {
            if (first_to_second[left_char] != right_char) {
                result = false;
                break;
            }
        } else {
            if (second_used[right_char]) {
                result = false;
                break;
            }

            first_to_second[left_char] = right_char;
            first_has_mapping[left_char] = true;
            second_used[right_char] = true;
        }
    }

    if (result && (*left != '\0' || *right != '\0')) {
        result = false;
    }

    free(first_to_second);
    free(first_has_mapping);
    free(second_used);

    return result;
}

int main(int argc, char *argv[])
{
    const char *program_name =
        argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return EXIT_FAILURE;
    }

    puts(are_isomorphic(argv[1], argv[2])
             ? "The strings are isomorphic."
             : "The strings are not isomorphic.");

    return EXIT_SUCCESS;
}