#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 256

void count_characters(const char *str, int *alphabets, int *digits, int *specials) {
    *alphabets = 0;
    *digits = 0;
    *specials = 0;
    
    if (str == NULL) {
        return;
    }
    
    while (*str != '\0') {
        if (isalpha((unsigned char)*str)) {
            (*alphabets)++;
        } else if (isdigit((unsigned char)*str)) {
            (*digits)++;
        } else {
            (*specials)++;
        }
        str++;
    }
}

int main(void) {
    char input[INPUT_BUFFER_SIZE + 1];
    int alphabets, digits, specials;
    
    memset(input, 0, sizeof(input));
    
    printf("Enter a string: ");
    if (fgets(input, (int)sizeof(input) - 1, stdin) == NULL) {
        return 1;
    }
    
    size_t len = strlen(input);
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (c == EOF) {
            clearerr(stdin);
        }
    }
    
    count_characters(input, &alphabets, &digits, &specials);
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", specials);
    
    return 0;
}