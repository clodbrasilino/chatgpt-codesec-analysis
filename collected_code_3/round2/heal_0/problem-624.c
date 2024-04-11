#include <stdio.h>
#include <ctype.h>
#include <string.h>

void convertToUpper(char* str) {
    int i = 0;
    while(str[i]) {
        str[i] = toupper(str[i]);
        i++;
    }
}

int main() {
    char str[] = "Hello, World!";
    convertToUpper(str);
    printf("%s\n", str);
    return 0;
}