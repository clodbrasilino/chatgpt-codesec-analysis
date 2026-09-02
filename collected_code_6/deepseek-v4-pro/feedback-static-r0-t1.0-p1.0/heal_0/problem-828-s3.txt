#include <stdio.h>
#include <ctype.h>

void count_characters(const char *str, int *alphabets, int *digits, int *special) {
    *alphabets = 0;
    *digits = 0;
    *special = 0;
    
    if (str == NULL) {
        return;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            (*alphabets)++;
        } else if (isdigit((unsigned char)str[i])) {
            (*digits)++;
        } else {
            (*special)++;
        }
    }
}

int main(void) {
    char input[1000];
    int alphabets = 0;
    int digits = 0;
    int special = 0;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    
    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    count_characters(input, &alphabets, &digits, &special);
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", special);
    
    return 0;
}