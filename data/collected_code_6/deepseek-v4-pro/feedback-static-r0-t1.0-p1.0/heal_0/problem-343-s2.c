#include <stdio.h>
#include <ctype.h>

int count_digits(const char *str) {
    int digits = 0;
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            digits++;
        }
        str++;
    }
    return digits;
}

int count_letters(const char *str) {
    int letters = 0;
    while (*str) {
        if (isalpha((unsigned char)*str)) {
            letters++;
        }
        str++;
    }
    return letters;
}

int main(void) {
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    
    int digits = count_digits(input);
    int letters = count_letters(input);
    
    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);
    
    return 0;
}