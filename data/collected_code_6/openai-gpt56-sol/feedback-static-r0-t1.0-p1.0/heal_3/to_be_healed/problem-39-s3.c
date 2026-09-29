#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum { INPUT_CAPACITY = 4096 };

static bool can_rearrange_without_adjacent_duplicates(
    const char *str,
    size_t length)
{
    size_t frequencies[256] = {0};
    size_t max_frequency = 0;

    if (str == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)str[i];

        ++frequencies[character];
        if (frequencies[character] > max_frequency) {
            max_frequency = frequencies[character];
        }
    }

    return max_frequency <= (length + 1U) / 2U;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (length == sizeof input - 1U) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
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

        if (ferror(stdin)) {
            return 1;
        }
    }

    if (length > 0U && input[length - 1U] == '\r') {
        input[--length] = '\0';
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    return 0;
}