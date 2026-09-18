#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char findMaxOccurringChar(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }

    int count[256] = {0};
    int maxCount = -1;
    char maxChar = '\0';

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char current_char = (unsigned char)str[i];
        count[current_char]++;
        
        if (count[current_char] > maxCount) {
            maxCount = count[current_char];
            maxChar = (char)current_char;
        }
    }

    return maxChar;
}

int main(void) {
    const char *testString = "sample string to find the maximum occurring character";
    
    char result = findMaxOccurringChar(testString);
    
    if (result != '\0') {
        printf("The maximum occurring character is: '%c'\n", result);
    } else {
        printf("Invalid string or empty string provided.\n");
    }

    return 0;
}