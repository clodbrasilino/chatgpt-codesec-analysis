#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

int count_digits_and_letters(const char *string, size_t *digits, size_t *letters)
{
    const unsigned char *current;

    if (string == NULL || digits == NULL || letters == NULL) {
        return -1;
    }

    *digits = 0;
    *letters = 0;
    current = (const unsigned char *)string;

    while (*current != '\0') {
        if (isdigit(*current) != 0) {
            ++(*digits);
        } else if (isalpha(*current) != 0) {
            ++(*letters);
        }

        ++current;
    }

    return 0;
}

int main(void)
{
    char input[1024];
    size_t digits;
    size_t letters;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }

        input[0] = '\0';
    }

    if (count_digits_and_letters(input, &digits, &letters) != 0) {
        fprintf(stderr, "Invalid argument.\n");
        return 1;
    }

    if (printf("Digits: %zu\nLetters: %zu\n", digits, letters) < 0) {
        return 1;
    }

    return 0;
}