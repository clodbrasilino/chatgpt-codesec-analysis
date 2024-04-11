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
    char str[] = "Hello World";
    printf("Length of last word: %d\n", lengthOfLastWord(str));
    return 0;
}