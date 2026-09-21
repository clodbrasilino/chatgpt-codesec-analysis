#include <stdio.h>
#include <stdlib.h>

static size_t count_character(const char *string, int character)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if ((unsigned char)*string == (unsigned char)character) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char target_input[3];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        int discarded;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            discarded = getchar();
        } while (discarded != '\n' && discarded != EOF);
    }

    if (fgets(target_input, sizeof target_input, stdin) == NULL) {
        fputs("Failed to read the character.\n", stderr);
        return EXIT_FAILURE;
    }

    if (target_input[0] == '\n' || target_input[0] == '\0') {
        fputs("No character was provided.\n", stderr);
        return EXIT_FAILURE;
    }

    if (target_input[1] != '\n' && target_input[1] != '\0') {
        int discarded;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            discarded = getchar();
        } while (discarded != '\n' && discarded != EOF);

        fputs("Provide exactly one character.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count_character(input, (unsigned char)target_input[0]));
    return EXIT_SUCCESS;
}