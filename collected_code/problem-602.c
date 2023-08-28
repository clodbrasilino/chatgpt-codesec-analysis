#include <stdio.h>

char findFirstRepeatedChar(char *string) {
    int count[256] = {0}; // assuming ASCII character set

    for (int i = 0; string[i] != '\0'; i++) {
        if (count[string[i]] == 1)
            return string[i];
        
        count[string[i]]++;
    }

    return '\0'; // no repeated characters found 
}

int main() {
    char string[] = "example";
    char result = findFirstRepeatedChar(string);

    printf("The first repeated character is: %c\n", result);

    return 0;
}