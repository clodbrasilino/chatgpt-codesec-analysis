#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uintmax_t alphabets;
    uintmax_t digits;
    uintmax_t special_characters;
} CharacterCounts;

static void update_count(CharacterCounts *counts, unsigned char character)
{
    if (isalpha((int)character) != 0) {
        ++counts->alphabets;
    } else if (isdigit((int)character) != 0) {
        ++counts->digits;
    } else {
        ++counts->special_characters;
    }
}

int main(void)
{
    CharacterCounts counts = {0, 0, 0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin)) > 0) {
        size_t i;

        for (i = 0; i < bytes_read; ++i) {
            update_count(&counts, buffer[i]);
        }
    }

    if (ferror(stdin) != 0) {
        return 1;
    }

    if (printf("Alphabets: %ju\n"
               "Digits: %ju\n"
               "Special characters: %ju\n",
               counts.alphabets,
               counts.digits,
               counts.special_characters) < 0) {
        return 1;
    }

    return 0;
}