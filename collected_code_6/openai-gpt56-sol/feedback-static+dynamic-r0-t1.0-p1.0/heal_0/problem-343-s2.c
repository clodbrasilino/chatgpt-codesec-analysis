#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    size_t digits;
    size_t letters;
} CharacterCounts;

static CharacterCounts count_digits_and_letters(const char *string)
{
    CharacterCounts counts = {0U, 0U};

    if (string == NULL) {
        return counts;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string;

        if (isdigit(character) != 0) {
            ++counts.digits;
        } else if (isalpha(character) != 0) {
            ++counts.letters;
        }

        ++string;
    }

    return counts;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        input[0] = '\0';
    }

    CharacterCounts counts = count_digits_and_letters(input);

    if (printf("Digits: %zu\nLetters: %zu\n",
               counts.digits,
               counts.letters) < 0) {
        return 1;
    }

    return 0;
}