#include <stdio.h>
#include <ctype.h>
#include <string.h>

void convertToLower(char* str) {
    int i = 0;
    while(str[i]) {
        str[i] = tolower(str[i]);
        i++;
    }
}

int main() {
    char str[] = "HELLO WORLD";
    convertToLower(str);
    printf("%s", str);
    return 0;
}