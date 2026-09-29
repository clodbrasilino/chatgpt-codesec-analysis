#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define BYTE_VALUES 256U

static bool are_isomorphic(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    bool first_mapped[BYTE_VALUES] = {false};
    bool second_mapped[BYTE_VALUES] = {false};
    unsigned char first_to_second[BYTE_VALUES] = {0};

    while (*first != '\0' && *second != '\0') {
        unsigned char first_char = (unsigned char)*first;
        unsigned char second_char = (unsigned char)*second;

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

    return *first == '\0' && *second == '\0';
}

int main(int argc, char *argv[])
{
    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
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