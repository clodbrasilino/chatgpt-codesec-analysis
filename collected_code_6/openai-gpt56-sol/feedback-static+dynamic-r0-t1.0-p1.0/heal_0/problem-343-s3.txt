#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

static void count_digits_and_letters(const char *string,
                                     size_t *digit_count,
                                     size_t *letter_count)
{
    size_t digits = 0U;
    size_t letters = 0U;

    if (string == NULL || digit_count == NULL || letter_count == NULL) {
        return;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string;

        if (isdigit(character) != 0) {
            ++digits;
        } else if (isalpha(character) != 0) {
            ++letters;
        }

        ++string;
    }

    *digit_count = digits;
    *letter_count = letters;
}

int main(void)
{
    char input[1024];
    size_t digits = 0U;
    size_t letters = 0U;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        input[0] = '\0';
    }

    count_digits_and_letters(input, &digits, &letters);

    if (printf("Digits: %zu\nLetters: %zu\n", digits, letters) < 0) {
        return 1;
    }

    return 0;
}