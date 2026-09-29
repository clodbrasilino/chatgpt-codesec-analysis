#include <stdio.h>
#include <ctype.h>
#include <string.h>

void count_digits_letters(const char *str, int *digits, int *letters) {
    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }

    *digits = 0;
    *letters = 0;

    while (*str != '\0') {
        if (isdigit((unsigned char)*str)) {
            (*digits)++;
        } else if (isalpha((unsigned char)*str)) {
            (*letters)++;
        }
        str++;
    }
}

int main(void) {
    char str[100];
    int digits = 0;
    int letters = 0;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    str[strcspn(str, "\n")] = '\0';

    count_digits_letters(str, &digits, &letters);

    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);

    return 0;
}