#include <stdio.h>
#include <ctype.h>
#include <string.h>

void convertToUpper(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    char str[] = "Hello, World!";
    convertToUpper(str);
    printf("%s\n", str);
    return 0;
}