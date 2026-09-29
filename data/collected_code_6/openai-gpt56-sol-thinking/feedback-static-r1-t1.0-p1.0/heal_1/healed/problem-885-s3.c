#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool strings_are_isomorphic(const char *first, const char *second)
{
    size_t alphabet_size;
    size_t *first_positions;
    size_t *second_positions;
    size_t position = 1;
    bool isomorphic = true;

    if (first == NULL || second == NULL) {
        return false;
    }

    if ((uintmax_t)UCHAR_MAX >= (uintmax_t)SIZE_MAX) {
        return false;
    }

    alphabet_size = (size_t)UCHAR_MAX + 1U;

    if (alphabet_size > SIZE_MAX / sizeof(*first_positions)) {
        return false;
    }

    first_positions = calloc(alphabet_size, sizeof(*first_positions));
    second_positions = calloc(alphabet_size, sizeof(*second_positions));

    if (first_positions == NULL || second_positions == NULL) {
        free(first_positions);
        free(second_positions);
        return false;
    }

    while (*first != '\0' && *second != '\0') {
        const unsigned char first_char = (unsigned char)*first;
        const unsigned char second_char = (unsigned char)*second;

        if (first_positions[first_char] != second_positions[second_char]) {
            isomorphic = false;
            break;
        }

        first_positions[first_char] = position;
        second_positions[second_char] = position;

        ++first;
        ++second;
        ++position;
    }

    if (*first != '\0' || *second != '\0') {
        isomorphic = false;
    }

    free(first_positions);
    free(second_positions);

    return isomorphic;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    const char *result;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return EXIT_FAILURE;
    }

    result = strings_are_isomorphic(argv[1], argv[2])
                 ? "The strings are isomorphic.\n"
                 : "The strings are not isomorphic.\n";

    if (fputs(result, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}