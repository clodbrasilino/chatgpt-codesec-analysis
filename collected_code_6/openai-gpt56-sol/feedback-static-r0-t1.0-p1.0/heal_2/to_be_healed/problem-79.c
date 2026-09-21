#include <stdio.h>

static int has_odd_length(const char *word, size_t length)
{
    return word != NULL && (length % 2U) != 0U;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[256];
    size_t length = 0U;
    int character;
    int truncated = 0;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length < sizeof word - 1U) {
            word[length++] = (char)character;
        } else {
            truncated = 1;
        }
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        return 1;
    }

    if (truncated) {
        return 1;
    }

    word[length] = '\0';

    printf("%s\n", has_odd_length(word, length) ? "Odd" : "Even");

    return 0;
}