#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define BYTE_VALUES ((size_t)UCHAR_MAX + 1U)

static bool are_isomorphic(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    bool first_mapped[BYTE_VALUES] = { false };
    bool second_mapped[BYTE_VALUES] = { false };
    unsigned char first_to_second[BYTE_VALUES] = { 0 };

    while (*first != '\0' && *second != '\0') {
        const unsigned char first_char = (unsigned char)*first;
        const unsigned char second_char = (unsigned char)*second;
        const size_t first_index = (size_t)first_char;
        const size_t second_index = (size_t)second_char;

        if (first_index >= BYTE_VALUES || second_index >= BYTE_VALUES) {
            return false;
        }

        if (first_mapped[first_index]) {
            if (first_to_second[first_index] != second_char) {
                return false;
            }
        } else {
            if (second_mapped[second_index]) {
                return false;
            }

            first_to_second[first_index] = second_char;
            first_mapped[first_index] = true;
            second_mapped[second_index] = true;
        }

        ++first;
        ++second;
    }

    return *first == '\0' && *second == '\0';
}

int main(int argc, char *const argv[])
{
    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        const char *program_name = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return 1;
    }

    puts(are_isomorphic(argv[1], argv[2])
             ? "The strings are isomorphic."
             : "The strings are not isomorphic.");

    return 0;
}