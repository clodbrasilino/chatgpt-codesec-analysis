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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];

    if (stream == NULL || counts == NULL) {
        return 0;
    }

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stream);

        for (size_t i = 0; i < bytes_read; ++i) {
            unsigned char c = buffer[i];

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

        if (bytes_read < sizeof buffer) {
            if (ferror(stream)) {
                return 0;
            }
            break;
        }
    }

    *counts = result;
    return 1;
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