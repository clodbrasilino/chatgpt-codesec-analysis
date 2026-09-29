#include <stdbool.h>
#include <stdio.h>

static bool all_characters_same(const char *string)
{
    if (string == NULL || string[0] == '\0') {
        return false;
    }

    const char first = string[0];

    for (size_t i = 1U; string[i] != '\0'; ++i) {
        if (string[i] != first) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 1;
        }

        input[0] = '\0';
    } else {
        size_t length = 0U;

        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] == '\n') {
            input[length] = '\0';
        } else if (!feof(stdin)) {
            int character;

            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = getchar();
            } while (character != '\n' && character != EOF);

            if (character == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return 1;
            }

            fputs("Input is too long.\n", stderr);
            return 1;
        }
    }

    puts(all_characters_same(input)
             ? "All characters are the same."
             : "Not all characters are the same.");

    return 0;
}