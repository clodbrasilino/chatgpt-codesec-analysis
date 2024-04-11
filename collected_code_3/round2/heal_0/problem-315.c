#include <stdio.h>
#include <string.h>
#include <ctype.h>

int maxLengthEvenWord(char* str) {
    int maxLen = 0;
    int currentLen = 0;
    int i = 0;

    while (str[i]) {
        if (isalpha(str[i])) {
            currentLen++;
        } else {
            if (currentLen % 2 == 0 && currentLen > maxLen) {
                maxLen = currentLen;
            }
            currentLen = 0;
        }
        i++;
    }

    if (currentLen % 2 == 0 && currentLen > maxLen) {
        maxLen = currentLen;
    }

    return maxLen;
}

int main() {
    char str[] = "Hello, I am a C developer";
    int maxLen = maxLengthEvenWord(str);
    printf("Maximum length of even word is: %d\n", maxLen);
    return 0;
}