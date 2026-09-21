#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool are_isomorphic(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    unsigned char mapping[UCHAR_MAX + 1U] = {0};
    bool mapped[UCHAR_MAX + 1U] = {false};
    bool used[UCHAR_MAX + 1U] = {false};

    const unsigned char *left = (const unsigned char *)first;
    const unsigned char *right = (const unsigned char *)second;

    while (*left != '\0' && *right != '\0') {
        const unsigned int left_index = *left;
        const unsigned int right_index = *right;

        if (mapped[left_index]) {
            if (mapping[left_index] != *right) {
                return false;
            }
        } else {
            if (used[right_index]) {
                return false;
            }

            mapping[left_index] = *right;
            mapped[left_index] = true;
            used[right_index] = true;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

int main(int argc, char *const argv[])
{
    const char *program_name = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return EXIT_FAILURE;
    }

    puts(are_isomorphic(argv[1], argv[2])
             ? "The strings are isomorphic."
             : "The strings are not isomorphic.");

    return EXIT_SUCCESS;
}