#include <stdio.h>
#include <string.h>

void replaceSpaceUnderscore(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (str[i] == ' ') {
            str[i] = '_';
        } else if (str[i] == '_') {
            str[i] = ' ';
        }
    }
}

int main() {
    char str[] = "Hello _World _";
    printf("Before: %s\n", str);
    replaceSpaceUnderscore(str);
    printf("After: %s\n", str);
    return 0;
}