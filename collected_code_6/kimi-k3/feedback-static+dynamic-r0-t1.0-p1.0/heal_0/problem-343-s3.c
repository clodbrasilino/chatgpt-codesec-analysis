#include <stdio.h>
#include <ctype.h>

void count_digits_and_letters(const char *str, int *digit_count, int *letter_count) {
    int i;
    *digit_count = 0;
    *letter_count = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            (*digit_count)++;
        } else if (isalpha((unsigned char)str[i])) {
            (*letter_count)++;
        }
    }
}

int main(void) {
    char str[100];
    int digit_count, letter_count;
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        count_digits_and_letters(str, &digit_count, &letter_count);
        printf("Number of digits: %d\n", digit_count);
        printf("Number of letters: %d\n", letter_count);
    }
    return 0;
}