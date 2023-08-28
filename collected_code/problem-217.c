#include <stdio.h>

char findFirstRepeatedChar(char* str) {
    int count[256] = {0}; // Assuming ASCII characters
    int length = strlen(str);
    
    for (int i = 0; i < length; i++) {
        count[str[i]]++;
        if (count[str[i]] > 1) {
            return str[i];
        }
    }
    
    return '\0'; // No repeated characters found
}

int main() {
    char str[] = "hello world";
    char firstRepeatedChar = findFirstRepeatedChar(str);
    
    if (firstRepeatedChar != '\0') {
        printf("The first repeated character is: %c\n", firstRepeatedChar);
    } else {
        printf("No repeated characters found\n");
    }
    
    return 0;
}