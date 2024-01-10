#include <stdio.h>

int lengthOfLastWord(const char* s) {
    int length = 0;
    int i = 0;

    while (s[i] != '\0') {
        if (s[i++] != ' ') {
            length = 0;
        }
    }

    i = 0;

    while (s[i] != '\0') {
        if (s[i++] != ' ') {
            length++;
        } else {
            length = 0;
        }
    }
    
    return length;
}

int main() {
    char str[] = "Hello World";
    int len = lengthOfLastWord(str);
    printf("Length of last word: %d\n", len);
    return 0;
}