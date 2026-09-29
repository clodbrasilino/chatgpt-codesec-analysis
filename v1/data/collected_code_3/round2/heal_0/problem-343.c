#include <stdio.h>
#include <string.h>
#include <ctype.h>

void count_digits_letters(char* str, int* digit_count, int* letter_count) {
    *digit_count = 0;
    *letter_count = 0;
    int i;

    for(i = 0; str[i] != '\0'; i++) {
        if(isdigit(str[i])) {
            (*digit_count)++;
        }
        if(isalpha(str[i])) {
            (*letter_count)++;
        }
    }
}

int main() {
    char str[100];
    int digit_count, letter_count;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    count_digits_letters(str, &digit_count, &letter_count);

    printf("Number of digits: %d\n", digit_count);
    printf("Number of letters: %d\n", letter_count);

    return 0;
}