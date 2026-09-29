#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool are_isomorphic(const char *first, const char *second)
{
    int forward[UCHAR_MAX + 1];
    int reverse[UCHAR_MAX + 1];

    if (first == NULL || second == NULL) {
        return false;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        forward[i] = -1;
        reverse[i] = -1;
    }

    while (*first != '\0' && *second != '\0') {
        const unsigned char left = (unsigned char)*first;
        const unsigned char right = (unsigned char)*second;

        if ((forward[left] != -1 && forward[left] != right) ||
            (reverse[right] != -1 && reverse[right] != left)) {
            return false;
        }

        forward[left] = right;
        reverse[right] = left;

        ++first;
        ++second;
    }

    return *first == '\0' && *second == '\0';
}

int main(int argc, char *const argv[])
{
    if (argc != 3) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr,
                    "Usage: %s <first-string> <second-string>\n",
                    program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (puts(are_isomorphic(argv[1], argv[2]) ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}