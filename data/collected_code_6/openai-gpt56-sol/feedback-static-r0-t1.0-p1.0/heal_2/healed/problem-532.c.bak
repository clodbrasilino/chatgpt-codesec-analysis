#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool are_permutations(const char *first, const char *second)
{
    size_t counts[256] = {0};

    if (first == NULL || second == NULL) {
        return false;
    }

    const size_t first_length = strlen(first);
    const size_t second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    for (size_t i = 0; i < first_length; ++i) {
        ++counts[(unsigned char)first[i]];
    }

    for (size_t i = 0; i < second_length; ++i) {
        const unsigned char character = (unsigned char)second[i];

        if (counts[character] == 0) {
            return false;
        }

        --counts[character];
    }

    return true;
}

int main(int argc, const char *const argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }

    if (are_permutations(argv[1], argv[2])) {
        puts("The strings are permutations of each other.");
    } else {
        puts("The strings are not permutations of each other.");
    }

    return 0;
}