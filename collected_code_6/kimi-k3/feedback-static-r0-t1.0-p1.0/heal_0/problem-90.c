#include <stdio.h>
#include <string.h>
#include <ctype.h>

int findLongestWordLength(const char *str) {
    int maxLength = 0;
    int currentLength = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (*str != '\0') {
        if (isalpha((unsigned char)*str)) {
            currentLength++;
        } else {
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
            currentLength = 0;
        }
        str++;
    }
    
    if (currentLength > maxLength) {
        maxLength = currentLength;
    }
    
    return maxLength;
}

int main(void) {
    const char *testString = "The quick brown fox jumps over the lazy dog";
    int result = findLongestWordLength(testString);
    
    printf("Longest word length: %d\n", result);
    
    return 0;
}