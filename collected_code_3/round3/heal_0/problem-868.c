#include <stdio.h>
#include <string.h>

int lengthOfLastWord(char* s) {
    int len = strlen(s), lastWordLength = 0;
    while (len > 0 && s[len - 1] == ' ') len--;
    while (len > 0 && s[len - 1] != ' ') {
        lastWordLength++;
        len--;
    }
    return lastWordLength;
}

int main() {
    char s[] = "Hello World";
    printf("%d", lengthOfLastWord(s));
    return 0;
}