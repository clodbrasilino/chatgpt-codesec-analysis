#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256
#define INPUT_SIZE 256

char find_first_repeated_char(const char *str) {
    int count[MAX_CHAR] = {0};
    
    if (str == NULL) {
        return '\0';
    }
    
    for (size_t i = 0; i < INPUT_SIZE - 1 && str[i] != '\0'; i++) {
        if (count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
        count[(unsigned char)str[i]]++;
    }
    
    return '\0';
}

int main(void) {
    char input[INPUT_SIZE] = {0};
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    char result = find_first_repeated_char(input);
    
    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }
    
    return 0;
}