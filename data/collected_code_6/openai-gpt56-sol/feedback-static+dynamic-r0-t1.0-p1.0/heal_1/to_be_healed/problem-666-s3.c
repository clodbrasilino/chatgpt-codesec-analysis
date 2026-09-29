#include <stdio.h>
#include <stdlib.h>

size_t count_char_occurrences(const char *string, char character)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (*string == character) {
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
    int character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    character = getchar();
    if (character == EOF) {
        fputs("Failed to read the character.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count_char_occurrences(input, (char)character));

    return EXIT_SUCCESS;
}