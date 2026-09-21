#include <stdio.h>

enum { WORD_CAPACITY = 256 };

static int has_even_length(const char *word, size_t length)
{
    return word != NULL && length % 2U == 0U;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[WORD_CAPACITY];
    size_t length = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1U >= sizeof word) {
            while (character != '\n' && character != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            }

            fprintf(stderr, "Input is too long.\n");
            return 1;
        }

        word[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    if (character == EOF && length == 0U) {
        return 1;
    }

    word[length] = '\0';

    puts(has_even_length(word, length) ? "Even" : "Odd");
    return 0;
}