#include <stdio.h>
#include <string.h>

char addChars(char* str) {
    int sum = 0;
    for(int i = 0; i < strlen(str); i++) {
        sum += str[i];
    }
    return (char)(sum % 256);
}

int main() {
    char str[] = "Hello World";
    char result = addChars(str);
    printf("The character obtained by adding all characters is: %c\n", result);
    return 0;
}