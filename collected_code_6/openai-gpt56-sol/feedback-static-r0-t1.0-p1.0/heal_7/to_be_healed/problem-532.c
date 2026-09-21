#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool get_string_length(const char *string, size_t maximum_length,
                              size_t *length)
{
    if (string == NULL || length == NULL) {
        return false;
    }

    const char *terminator = memchr(string, '\0', maximum_length);

    if (terminator == NULL) {
        return false;
    }

    *length = (size_t)(terminator - string);
    return true;
}

static bool are_permutations(const char *first, size_t first_length,
                             const char *second, size_t second_length)
{
    size_t counts[256] = {0};

    if (first == NULL || second == NULL || first_length != second_length) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    const size_t maximum_argument_length = 1048576;
    size_t first_length;
    size_t second_length;

    if (argc != 3 || argv == NULL) {
        const char *program_name = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return 1;
    }

    if (argv[1] == NULL || argv[2] == NULL) {
        fputs("Invalid null argument.\n", stderr);
        return 1;
    }

    if (!get_string_length(argv[1], maximum_argument_length, &first_length) ||
        !get_string_length(argv[2], maximum_argument_length, &second_length)) {
        fputs("Argument is not null-terminated within the allowed length.\n",
              stderr);
        return 1;
    }

    if (are_permutations(argv[1], first_length, argv[2], second_length)) {
        puts("The strings are permutations of each other.");
    } else {
        puts("The strings are not permutations of each other.");
    }

    return 0;
}