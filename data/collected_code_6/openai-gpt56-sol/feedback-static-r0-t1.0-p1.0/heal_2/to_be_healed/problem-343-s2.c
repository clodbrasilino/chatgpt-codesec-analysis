#include <ctype.h>
#include <stdio.h>

typedef struct {
    size_t digits;
    size_t letters;
} CharacterCounts;

static int count_digits_and_letters(CharacterCounts *counts)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];

    counts->digits = 0;
    counts->letters = 0;

    while (fgets((char *)buffer, sizeof buffer, stdin) != NULL) {
        for (size_t i = 0; buffer[i] != '\0'; ++i) {
            if (isdigit(buffer[i]) != 0) {
                ++counts->digits;
            } else if (isalpha(buffer[i]) != 0) {
                ++counts->letters;
            }
        }
    }

    return ferror(stdin) == 0;
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