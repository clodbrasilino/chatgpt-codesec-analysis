#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    size_t digits;
    size_t letters;
} CharacterCounts;

static int count_digits_and_letters(FILE *stream, CharacterCounts *counts)
{
    CharacterCounts result = {0, 0};
    int ch;

    if (stream == NULL || counts == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF) {
        unsigned char c = (unsigned char)ch;

        if (isdigit(c)) {
            if (result.digits == SIZE_MAX) {
                return 0;
            }
            ++result.digits;
        } else if (isalpha(c)) {
            if (result.letters == SIZE_MAX) {
                return 0;
            }
            ++result.letters;
        }
    }

    if (ferror(stream)) {
        return 0;
    }

    *counts = result;
    return 1;
}

int main(void)
{
    CharacterCounts counts;

    if (!count_digits_and_letters(stdin, &counts)) {
        return 1;
    }

    if (printf("Digits: %zu\nLetters: %zu\n",
               counts.digits, counts.letters) < 0) {
        return 1;
    }

    return 0;
}