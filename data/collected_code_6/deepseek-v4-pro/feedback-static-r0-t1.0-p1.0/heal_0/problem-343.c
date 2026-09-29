#include <stdio.h>
#include <ctype.h>

void count_digits_letters(const char *str, int *digits, int *letters) {
    *digits = 0;
    *letters = 0;
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            (*digits)++;
        } else if (isalpha((unsigned char)*str)) {
            (*letters)++;
        }
        str++;
    }
}

int main(void) {
    const char *test_string = "Hello123World456";
    int digit_count = 0;
    int letter_count = 0;
    
    count_digits_letters(test_string, &digit_count, &letter_count);
    
    printf("String: %s\n", test_string);
    printf("Digits: %d\n", digit_count);
    printf("Letters: %d\n", letter_count);
    
    return 0;
}