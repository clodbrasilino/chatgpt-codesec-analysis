#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define MAX_CHAR 256
#define INPUT_BUFFER_SIZE 256

char find_first_repeated_char(const char *str) {
    int count[MAX_CHAR] = {0};
    
    if (str == NULL) {
        return '\0';
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
        count[(unsigned char)str[i]]++;
    }
    
    return '\0';
}

int main(void) {
    char input[INPUT_BUFFER_SIZE] = {0};
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    size_t len = 0;
    while (len < sizeof(input) && input[len] != '\0') {
        len++;
    }
    
    if (len == 0) {
        printf("No repeated character found\n");
        return 0;
    }
    
    if (len < sizeof(input) && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (c == EOF) {
            clearerr(stdin);
        }
    }
    
    char result = find_first_repeated_char(input);
    
    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }
    
    return 0;
}