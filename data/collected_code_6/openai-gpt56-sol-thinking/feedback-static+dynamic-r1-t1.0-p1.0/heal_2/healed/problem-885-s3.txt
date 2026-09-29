#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char value;
    bool assigned;
} CharacterMapping;

bool strings_are_isomorphic(const char *first, const char *second)
{
    CharacterMapping *first_to_second;
    CharacterMapping *second_to_first;
    size_t character_count;
    bool result = true;

    if (first == NULL || second == NULL) {
        return false;
    }

    if ((uintmax_t)UCHAR_MAX >= (uintmax_t)SIZE_MAX) {
        return false;
    }

    character_count = (size_t)UCHAR_MAX + 1U;

    if (character_count > SIZE_MAX / sizeof(*first_to_second)) {
        return false;
    }

    first_to_second = calloc(character_count, sizeof(*first_to_second));
    if (first_to_second == NULL) {
        return false;
    }

    second_to_first = calloc(character_count, sizeof(*second_to_first));
    if (second_to_first == NULL) {
        free(first_to_second);
        return false;
    }

    while (*first != '\0' && *second != '\0') {
        unsigned char first_char = (unsigned char)*first;
        unsigned char second_char = (unsigned char)*second;
        CharacterMapping *forward = &first_to_second[first_char];
        CharacterMapping *reverse = &second_to_first[second_char];

        if (!forward->assigned && !reverse->assigned) {
            forward->value = second_char;
            forward->assigned = true;
            reverse->value = first_char;
            reverse->assigned = true;
        } else if (!forward->assigned ||
                   !reverse->assigned ||
                   forward->value != second_char ||
                   reverse->value != first_char) {
            result = false;
            break;
        }

        ++first;
        ++second;
    }

    if (result) {
        result = (*first == '\0' && *second == '\0');
    }

    free(second_to_first);
    free(first_to_second);

    return result;
}

int main(int argc, char **argv)
{
    const char *program_name;
    const char *message;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return EXIT_FAILURE;
    }

    message = strings_are_isomorphic(argv[1], argv[2])
                  ? "The strings are isomorphic.\n"
                  : "The strings are not isomorphic.\n";

    if (fputs(message, stdout) == EOF || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}