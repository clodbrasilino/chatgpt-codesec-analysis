#include <stdio.h>
#include <ctype.h>
#include <string.h>

void convertToUpper(char* str, int size) {
    for (int i = 0; i < size; i++) {
        if(str[i] == '\0'){
            break;
        }
        str[i] = toupper((unsigned char) str[i]);
    }
}

int main() {
    char str[] = "Hello, World!";
    convertToUpper(str, sizeof(str) / sizeof(str[0]));
    printf("%s\n", str);
    return 0;
}