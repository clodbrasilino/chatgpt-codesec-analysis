#include <ctype.h>
#include <stdio.h>

typedef struct {
    size_t digits;
    size_t letters;
} CharacterCounts;

static int count_digits_and_letters(CharacterCounts *counts)
{
    int character;

    if (counts == NULL) {
        return 0;
    }

    counts->digits = 0;
    counts->letters = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        unsigned char value = (unsigned char)character;

        if (isdigit(value)) {
            ++counts->digits;
        } else if (isalpha(value)) {
            ++counts->letters;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    CharacterCounts counts;

    if (!count_digits_and_letters(&counts)) {
        return 1;
    }

    if (printf("Digits: %zu\nLetters: %zu\n",
               counts.digits,
               counts.letters) < 0) {
        return 1;
    }

    return 0;
}