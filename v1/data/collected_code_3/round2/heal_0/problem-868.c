#include <stdio.h>
#include <string.h>

int lengthOfLastWord(char* s) {
    int len = strlen(s), lastLen = 0;
    while (len > 0 && s[len - 1] == ' ') len--;
    while (len > 0 && s[len - 1] != ' ') {
        len--;
        lastLen++;
    }
    return lastLen;
}

int main() {
    char str[] = "Hello World";
    int len = lengthOfLastWord(str);
    printf("Length of last word: %d\n", len);
    return 0;
}