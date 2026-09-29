#include <stdio.h>
#include <ctype.h>
#include <string.h>

void count_characters(const char *str, int *alphabets, int *digits, int *specials) {
    *alphabets = 0;
    *digits = 0;
    *specials = 0;
    
    while (*str) {
        if (isalpha(*str)) {
            (*alphabets)++;
        } else if (isdigit(*str)) {
            (*digits)++;
        } else if (!isspace(*str)) {
            (*specials)++;
        }
        str++;
    }
}

int main() {
    const char *input = "Hello, World! 123";
    int alphabets, digits, specials;

    count_characters(input, &alphabets, &digits, &specials);

    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", specials);

    return 0;
}