#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    size_t digits;
    size_t letters;
} CharacterCounts;

static int count_digits_and_letters(FILE *stream, CharacterCounts *counts)
{
    int ch;

    if (stream == NULL || counts == NULL) {
        return 0;
    }

    counts->digits = 0;
    counts->letters = 0;

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF) {
            return ferror(stream) == 0;
        }

        unsigned char c = (unsigned char)ch;

        if (isdigit(c) != 0) {
            if (counts->digits == SIZE_MAX) {
                return 0;
            }
            ++counts->digits;
        } else if (isalpha(c) != 0) {
            if (counts->letters == SIZE_MAX) {
                return 0;
            }
            ++counts->letters;
        }
    }
}

int main(void)
{
    CharacterCounts counts = {0, 0};

    if (!count_digits_and_letters(stdin, &counts)) {
        return 1;
    }

    if (printf("Digits: %zu\nLetters: %zu\n",
               counts.digits, counts.letters) < 0) {
        return 1;
    }

    return 0;
}