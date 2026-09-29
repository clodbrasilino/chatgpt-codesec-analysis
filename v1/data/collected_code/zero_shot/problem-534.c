#include <stdio.h>
#include <string.h>

void searchString(const char* pattern, const char* str) {
    int patternLength = strlen(pattern);
    int strLength = strlen(str);
    int i, j;
    
    for (i = 0; i <= strLength - patternLength; i++) {
        for (j = 0; j < patternLength; j++) {
            if (str[i + j] != pattern[j]) {
                break;
            }
        }
        
        if (j == patternLength) {
            printf("Pattern found at index %d\n", i);
        }
    }
}

int main() {
    const char* str = "This is a test string";
    const char* pattern = "test";
    
    searchString(pattern, str);
    
    return 0;
}