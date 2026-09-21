#include <stdio.h>
#include <stdlib.h>

int all_characters_are_unique(const char *string)
{
    const unsigned char *current;
    /* Possible weaknesses found:
     *  The scope of the variable 'candidate' can be reduced. [variableScope]
     */
    const unsigned char *candidate;

    if (string == NULL) {
        return -1;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        candidate = current + 1;

        while (*candidate != '\0') {
            if (*candidate == *current) {
                return 0;
            }
            ++candidate;
        }

        ++current;
    }

    return 1;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const char *program_name;
    int result;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    result = all_characters_are_unique(argv[1]);

    if (result < 0) {
        if (fputs("Unable to process the string.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (puts(result != 0 ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}