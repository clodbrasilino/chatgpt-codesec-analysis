#include <stdio.h>
#include <ctype.h>
#include <string.h>

void count_digits_letters(const char *str, int *digits, int *letters) {
    *digits = 0;
    *letters = 0;
    while (*str) {
        if (isdigit(*str)) {
            (*digits)++;
        } else if (isalpha(*str)) {
            (*letters)++;
        }
        str++;
    }
}

int main() {
    const char *input = "Hello123";
    int digits, letters;
    count_digits_letters(input, &digits, &letters);
    printf("Digits: %d, Letters: %d\n", digits, letters);
    return 0;
}