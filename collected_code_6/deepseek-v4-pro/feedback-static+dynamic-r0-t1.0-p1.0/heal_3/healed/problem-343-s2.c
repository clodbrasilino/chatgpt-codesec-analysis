#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 256

int count_digits(const char *str, size_t max_len) {
    int digits = 0;
    size_t i;
    for (i = 0; i < max_len; i++) {
        if (isdigit((unsigned char)str[i])) {
            digits++;
        }
    }
    return digits;
}

int count_letters(const char *str, size_t max_len) {
    int letters = 0;
    size_t i;
    for (i = 0; i < max_len; i++) {
        if (isalpha((unsigned char)str[i])) {
            letters++;
        }
    }
    return letters;
}

int main(void) {
    char input[BUFFER_SIZE];
    size_t input_len;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    
    input_len = strnlen(input, sizeof(input));
    if (input_len == sizeof(input) && input[input_len - 1] != '\0') {
        printf("Input too long.\n");
        return 1;
    }
    
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }
    
    int digits = count_digits(input, input_len);
    int letters = count_letters(input, input_len);
    
    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);
    
    return 0;
}