#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

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
    char input[256];
    int alphabets, digits, specials;
    size_t len;
    size_t max_input;
    int buffer_full;
    
    max_input = sizeof(input);
    buffer_full = 0;
    
    printf("Enter a string: ");
    if (fgets(input, max_input, stdin) == NULL) {
        return 1;
    }
    
    len = strnlen(input, max_input);
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        buffer_full = 1;
    }
    
    if (buffer_full) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (ferror(stdin)) {
                clearerr(stdin);
                break;
            }
        }
    }
    
    count_characters(input, &alphabets, &digits, &specials);
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", specials);
    
    return 0;
}