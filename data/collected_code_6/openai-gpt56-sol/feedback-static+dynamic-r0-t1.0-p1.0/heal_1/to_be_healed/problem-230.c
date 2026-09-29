#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_spaces(char *string, char replacement)
{
    if (string == NULL || replacement == '\0') {
        return -1;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        if (string[i] == ' ') {
            string[i] = replacement;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    int replacement_input;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (length == sizeof input - 1) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch != '\n') {
            return EXIT_FAILURE;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    replacement_input = getchar();

    if (replacement_input == EOF || replacement_input == '\0') {
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, (char)replacement_input) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}