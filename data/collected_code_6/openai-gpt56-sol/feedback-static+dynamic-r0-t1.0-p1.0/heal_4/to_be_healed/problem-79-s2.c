#include <stdbool.h>
#include <stdio.h>

enum { WORD_CAPACITY = 256 };

static bool has_odd_length(size_t length)
{
    return length % 2U != 0U;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[WORD_CAPACITY];

    if (fgets(word, sizeof word, stdin) == NULL) {
        return 1;
    }

    size_t length = 0U;

    while (word[length] != '\0' && word[length] != '\n') {
        ++length;
    }

    if (word[length] == '\n') {
        /* Possible weaknesses found:
         *  Variable 'word[length]' is assigned a value that is never used. [unreadVariable]
         */
        word[length] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }
            return 1;
        }

        if (character == EOF && ferror(stdin)) {
            return 1;
        }
    }

    if (length == 0U && feof(stdin)) {
        return 1;
    }

    puts(has_odd_length(length) ? "Odd" : "Even");
    return 0;
}