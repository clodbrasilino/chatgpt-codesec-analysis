#include <stdio.h>
#include <ctype.h>
#include <string.h>

void convertToLower(char* str) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

int main() {
    char str[] = "HELLO WORLD";
    convertToLower(str);
    printf("%s", str);
    return 0;
}