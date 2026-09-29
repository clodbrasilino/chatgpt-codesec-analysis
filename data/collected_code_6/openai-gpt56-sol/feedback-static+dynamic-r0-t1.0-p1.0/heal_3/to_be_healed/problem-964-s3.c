#include <stdbool.h>
#include <stdio.h>

enum { MAX_WORD_LENGTH = 255 };

static bool has_even_length(size_t length)
{
    return length % 2U == 0U;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_WORD_LENGTH + 2U];
    size_t length = 0U;
    int character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    while (input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && length > MAX_WORD_LENGTH) {
        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        if (ferror(stdin)) {
            return 1;
        }

        fputs("Input is too long.\n", stderr);
        return 1;
    }

    if (input[length] == '\0' && !feof(stdin)) {
        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        if (ferror(stdin)) {
            return 1;
        }

        fputs("Input is too long.\n", stderr);
        return 1;
    }

    if (length == 0U && input[0] == '\0') {
        return 1;
    }

    puts(has_even_length(length) ? "Even" : "Odd");
    return 0;
}