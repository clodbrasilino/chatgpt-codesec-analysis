#include <string.h>
#include <stdio.h>

int lengthOfLastWord(char *s) {
    int len = strlen(s), lastWordLen = 0;

    if (len == 0) 
        return 0;

    while (len > 0 && s[len - 1] == ' ') 
        len--;
    while (len > 0 && s[--len] != ' ')
        lastWordLen++;

    return lastWordLen;
}

int main() {
    char str[] = "Hello World";
    int length = lengthOfLastWord(str);
    printf("Length of last word: %d\n", length);
    return 0;
}