#include <ctype.h>
#include <stdio.h>

typedef struct {
    size_t alphabets;
    size_t digits;
    size_t special_characters;
} CharacterCounts;

CharacterCounts count_characters(const char *string)
{
    CharacterCounts counts = {0U, 0U, 0U};

    if (string == NULL) {
        return counts;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string;

        if (isalpha(character) != 0) {
            ++counts.alphabets;
        } else if (isdigit(character) != 0) {
            ++counts.digits;
        } else {
            ++counts.special_characters;
        }

        ++string;
    }

    return counts;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        return 0;
    }

    CharacterCounts counts = count_characters(input);

    if (printf("Alphabets: %zu\nDigits: %zu\nSpecial characters: %zu\n",
               counts.alphabets,
               counts.digits,
               counts.special_characters) < 0) {
        return 1;
    }

    return 0;
}