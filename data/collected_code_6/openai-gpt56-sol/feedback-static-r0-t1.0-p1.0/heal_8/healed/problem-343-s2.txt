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
    unsigned char buffer[4096];
    size_t bytes_read;

    if (stream == NULL || counts == NULL) {
        return 0;
    }

    while ((bytes_read = fread(buffer, 1, sizeof buffer, stream)) > 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            int c = buffer[i];

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