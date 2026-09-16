#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

int count_digits_letters(const char *str, size_t *digits, size_t *letters)
{
    size_t i;

    if (str == NULL || digits == NULL || letters == NULL) {
        return -1;
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

    return 0;
}

int main(void)
{
    char buffer[256];
    size_t digits = 0;
    size_t letters = 0;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    if (count_digits_letters(buffer, &digits, &letters) != 0) {
        fprintf(stderr, "Error counting characters\n");
        return 1;
    }

    printf("Digits: %zu\n", digits);
    printf("Letters: %zu\n", letters);

    return 0;
}