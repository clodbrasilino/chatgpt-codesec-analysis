#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

static bool are_isomorphic(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    bool second_used[UCHAR_MAX + 1] = {false};
    unsigned char first_to_second[UCHAR_MAX + 1] = {0};
    bool first_has_mapping[UCHAR_MAX + 1] = {false};

    while (*first != '\0' && *second != '\0') {
        unsigned char first_char = (unsigned char)*first++;
        unsigned char second_char = (unsigned char)*second++;

        if (first_has_mapping[first_char]) {
            if (first_to_second[first_char] != second_char) {
                return false;
            }
        } else {
            if (second_used[second_char]) {
                return false;
            }

            first_to_second[first_char] = second_char;
            first_has_mapping[first_char] = true;
            second_used[second_char] = true;
        }
    }

    return *first == '\0' && *second == '\0';
}

int main(int argc, char *argv[])
{
    const char *program_name =
        argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

    if (argc != 3 || argv == NULL) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return 1;
    }

    puts(are_isomorphic(argv[1], argv[2])
             ? "The strings are isomorphic."
             : "The strings are not isomorphic.");

    return 0;
}