#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    size_t digits;
    size_t letters;
} CharacterCounts;

static int count_digits_and_letters(FILE *stream, CharacterCounts *counts)
{
    unsigned char buffer[4096];
    size_t bytes_read;

    if (stream == NULL || counts == NULL) {
        return 0;
    }

    counts->digits = 0;
    counts->letters = 0;

    while ((bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stream)) > 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            if (isdigit(buffer[i])) {
                if (counts->digits == SIZE_MAX) {
                    return 0;
                }
                ++counts->digits;
            } else if (isalpha(buffer[i])) {
                if (counts->letters == SIZE_MAX) {
                    return 0;
                }
                ++counts->letters;
            }
        }
    }

    return !ferror(stream);
}

int main(void)
{
    CharacterCounts counts;

    if (!count_digits_and_letters(stdin, &counts)) {
        return 1;
    }

    if (printf("Digits: %zu\nLetters: %zu\n",
               counts.digits,
               counts.letters) < 0) {
        return 1;
    }

    return 0;
}