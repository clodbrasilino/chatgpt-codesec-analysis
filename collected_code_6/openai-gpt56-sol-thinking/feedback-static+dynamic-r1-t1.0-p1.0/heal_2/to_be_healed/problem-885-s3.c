#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

bool strings_are_isomorphic(const char *first, const char *second)
{
    unsigned char *first_to_second;
    unsigned char *second_to_first;
    size_t character_count;
    bool result = true;

    if (first == NULL || second == NULL) {
        return false;
    }

    character_count = (size_t)UCHAR_MAX;
    if (character_count == (size_t)-1) {
        return false;
    }
    ++character_count;

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

        if (first_to_second[first_char] == 0 &&
            second_to_first[second_char] == 0) {
            first_to_second[first_char] = second_char;
            second_to_first[second_char] = first_char;
        } else if (first_to_second[first_char] != second_char ||
                   second_to_first[second_char] != first_char) {
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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
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

    if (fputs(result, stdout) == EOF || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}