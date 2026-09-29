#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int first_non_repeated_character(const char *str, unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    const unsigned char *current;

    if (str == NULL || result == NULL) {
        return 0;
    }

    current = (const unsigned char *)str;

    while (*current != '\0') {
        ++frequencies[*current];
        ++current;
    }

    current = (const unsigned char *)str;

    while (*current != '\0') {
        if (frequencies[*current] == 1) {
            *result = *current;
            return 1;
        }
        ++current;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    unsigned char result;
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
        } else {
            fprintf(stderr, "No input provided.\n");
        }
        return 1;
    }

    for (length = 0; length < sizeof input && input[length] != '\0' &&
                     input[length] != '\n'; ++length) {
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (length == sizeof input - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            fprintf(stderr, "Input is too long.\n");
            return 1;
        }
    }

    if (first_non_repeated_character(input, &result)) {
        printf("%c\n", (int)result);
    } else {
        puts("No non-repeated character found.");
    }

    return 0;
}