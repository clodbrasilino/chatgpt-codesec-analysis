#include <stdio.h>
#include <string.h>

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

    if (fgets(word, sizeof word, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(word, "\r\n");

    if (word[length] == '\0' && !feof(stdin)) {
        int character;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((character = getchar()) != '\n' && character != EOF) {
        }

        return 1;
    }

    word[length] = '\0';

    if (ferror(stdin)) {
        return 1;
    }

    puts(has_odd_length(word, length) ? "Odd" : "Even");

    return 0;
}