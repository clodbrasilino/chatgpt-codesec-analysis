#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define INPUT_SIZE 256

void count_digits_and_letters(const char *str, int *digit_count, int *letter_count) {
    *digit_count = 0;
    *letter_count = 0;
    
    if (str == NULL) {
        return;
    }

    for (size_t i = 0; i < INPUT_SIZE && str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            (*digit_count)++;
        } else if (isalpha((unsigned char)str[i])) {
            (*letter_count)++;
        }
    }
}

int main(void) {
    char input[INPUT_SIZE];
    int digits = 0;
    int letters = 0;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[sizeof(input) - 1] = '\0';

    size_t len = 0;
    while (len < sizeof(input) && input[len] != '\0') {
        len++;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    count_digits_and_letters(input, &digits, &letters);

    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);

    return 0;
}