#include <stdio.h>
#include <string.h>
#include <ctype.h>

int maxEvenWordLength(char* str) {
    int maxLen = 0;
    int currLen = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            currLen++;
        } else {
            if (currLen % 2 == 0 && currLen > maxLen) {
                maxLen = currLen;
            }
            currLen = 0;
        }
    }
    if (currLen % 2 == 0 && currLen > maxLen) {
        maxLen = currLen;
    }
    return maxLen;
}

int main() {
    char str[] = "Hello world this is a test string";
    int maxLen = maxEvenWordLength(str);
    printf("Maximum length of even word is: %d\n", maxLen);
    return 0;
}