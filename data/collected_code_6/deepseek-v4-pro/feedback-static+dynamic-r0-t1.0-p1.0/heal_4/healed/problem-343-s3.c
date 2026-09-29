#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 256
#define MAX_INPUT_LENGTH (INPUT_BUFFER_SIZE - 1)

void count_digits_and_letters(const char *str, int *digit_count, int *letter_count) {
    *digit_count = 0;
    *letter_count = 0;

    if (str == NULL) {
        return;
    }

    size_t i = 0;
    while (i < MAX_INPUT_LENGTH && str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            (*digit_count)++;
        } else if (isalpha((unsigned char)str[i])) {
            (*letter_count)++;
        }
        i++;
    }
}

int main(void) {
    char input[INPUT_BUFFER_SIZE];
    int digits = 0;
    int letters = 0;

    printf("Enter a string: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[sizeof(input) - 1] = '\0';

    char *newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    count_digits_and_letters(input, &digits, &letters);

    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);

    return 0;
}