#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t count_characters(const char *string)
{
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return string == NULL ? 0U : strlen(string);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    input[strcspn(input, "\n")] = '\0';
    printf("%zu\n", count_characters(input));

    return EXIT_SUCCESS;
}