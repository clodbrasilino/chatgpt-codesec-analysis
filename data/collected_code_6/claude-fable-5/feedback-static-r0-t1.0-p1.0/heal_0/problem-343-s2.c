#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

void count_digits_letters(const char *str, size_t *digits, size_t *letters)
{
    size_t i;

    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }

    *digits = 0;
    *letters = 0;

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isdigit(c)) {
            (*digits)++;
        } else if (isalpha(c)) {
            (*letters)++;
        }
    }
}

int main(void)
{
    char input[256];
    size_t digits = 0;
    size_t letters = 0;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    count_digits_letters(input, &digits, &letters);

    printf("Digits: %zu\n", digits);
    printf("Letters: %zu\n", letters);

    return 0;
}