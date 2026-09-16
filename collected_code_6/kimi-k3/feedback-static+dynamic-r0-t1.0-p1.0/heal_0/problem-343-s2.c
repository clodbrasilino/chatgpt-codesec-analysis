#include <stdio.h>
#include <ctype.h>
#include <string.h>

void count_digits_letters(const char *str, size_t *digits, size_t *letters) {
    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }
    
    *digits = 0;
    *letters = 0;
    
    while (*str != '\0') {
        unsigned char c = (unsigned char)*str;
        if (isdigit(c)) {
            (*digits)++;
        } else if (isalpha(c)) {
            (*letters)++;
        }
        str++;
    }
}

int main(void) {
    char buffer[256];
    size_t digit_count = 0;
    size_t letter_count = 0;
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    count_digits_letters(buffer, &digit_count, &letter_count);
    
    printf("Digits: %zu\n", digit_count);
    printf("Letters: %zu\n", letter_count);
    
    return 0;
}