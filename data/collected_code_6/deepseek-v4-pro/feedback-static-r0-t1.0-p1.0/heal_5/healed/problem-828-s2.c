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
    size_t len;
    int c;
    
    memset(input, 0, sizeof(input));
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    len = strlen(input);
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        c = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
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