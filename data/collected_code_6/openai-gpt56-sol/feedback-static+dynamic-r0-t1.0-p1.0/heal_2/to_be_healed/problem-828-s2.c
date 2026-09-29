#include <ctype.h>
#include <stdio.h>

typedef struct {
    size_t alphabets;
    size_t digits;
    size_t special_characters;
} CharacterCounts;

static void update_counts(CharacterCounts *counts, const char *buffer)
{
    while (*buffer != '\0') {
        unsigned char character = (unsigned char)*buffer++;

        if (isalpha(character) != 0) {
            ++counts->alphabets;
        } else if (isdigit(character) != 0) {
            ++counts->digits;
        } else {
            ++counts->special_characters;
        }
    }
}

int main(void)
{
    CharacterCounts counts = {0U, 0U, 0U};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    while (fgets(input, sizeof input, stdin) != NULL) {
        update_counts(&counts, input);
    }

    if (ferror(stdin) != 0) {
        return 1;
    }

    if (printf("Alphabets: %zu\n"
               "Digits: %zu\n"
               "Special characters: %zu\n",
               counts.alphabets,
               counts.digits,
               counts.special_characters) < 0) {
        return 1;
    }

    return 0;
}