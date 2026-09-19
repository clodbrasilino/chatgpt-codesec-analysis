#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool are_isomorphic(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    const size_t first_length = strlen(first);
    const size_t second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    unsigned char first_to_second[256] = {0};
    bool first_mapped[256] = {false};
    bool second_mapped[256] = {false};

    for (size_t i = 0; i < first_length; ++i) {
        const unsigned char first_char = (unsigned char)first[i];
        const unsigned char second_char = (unsigned char)second[i];

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

int main(int argc, const char *const argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }

    puts(are_isomorphic(argv[1], argv[2])
             ? "The strings are isomorphic."
             : "The strings are not isomorphic.");

    return 0;
}