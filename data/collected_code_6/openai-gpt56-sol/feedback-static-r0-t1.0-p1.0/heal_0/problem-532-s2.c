#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool are_permutations(const char *first, const char *second)
{
    size_t frequencies[256] = {0};
    size_t first_length;
    size_t second_length;

    if (first == NULL || second == NULL) {
        return false;
    }

    first_length = strlen(first);
    second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    for (size_t i = 0; i < first_length; ++i) {
        ++frequencies[(unsigned char)first[i]];
    }

    for (size_t i = 0; i < second_length; ++i) {
        unsigned char character = (unsigned char)second[i];

        if (frequencies[character] == 0) {
            return false;
        }

        --frequencies[character];
    }

    return true;
}

int main(void)
{
    char first[1024];
    char second[1024];

    if (fgets(first, sizeof first, stdin) == NULL) {
        return 1;
    }

    if (fgets(second, sizeof second, stdin) == NULL) {
        return 1;
    }

    first[strcspn(first, "\n")] = '\0';
    second[strcspn(second, "\n")] = '\0';

    if (are_permutations(first, second)) {
        if (puts("The strings are permutations of each other.") == EOF) {
            return 1;
        }
    } else {
        if (puts("The strings are not permutations of each other.") == EOF) {
            return 1;
        }
    }

    return 0;
}