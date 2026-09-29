#include <stdio.h>
#include <string.h>
#include <ctype.h>

void countDigitsAndLetters(const char *str, int *digits, int *letters) {
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
    countDigitsAndLetters(input, &digits, &letters);
    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);
    return 0;
}