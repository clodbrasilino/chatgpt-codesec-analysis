#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool are_isomorphic(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    const unsigned char *left_begin = (const unsigned char *)first;
    const unsigned char *right_begin = (const unsigned char *)second;
    const unsigned char *left = left_begin;
    const unsigned char *right = right_begin;

    while (*left != '\0' && *right != '\0') {
        const unsigned char *previous_left = left_begin;
        const unsigned char *previous_right = right_begin;

        while (previous_left != left) {
            if ((*previous_left == *left && *previous_right != *right) ||
                (*previous_right == *right && *previous_left != *left)) {
                return false;
            }

            ++previous_left;
            ++previous_right;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    if (argc != 3) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

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