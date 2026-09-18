#include <stdio.h>
#include <string.h>

void ReplaceChars(char* str, int n) {
    int count = 0;

    for(int i = 0; i < strlen(str) && count < n; i++) {
        if(str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
            count++;
        }
    }
}

int main(void) {
    char str[] = "Hello, World. This is a test string.";

    ReplaceChars(str, 5);
    printf("%s\n", str);

    return 0;
}