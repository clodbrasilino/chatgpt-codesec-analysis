#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256

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
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    char result = find_first_repeated_char(input);
    
    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }
    
    return 0;
}