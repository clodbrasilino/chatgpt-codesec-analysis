#include <stdio.h>

int stringLength(char* str) {
    int len = 0;
    while(str[len] != '\0') {
        len++;
    }
    return len;  
}

int main() {
    char str[] = "Hello, World!";
    int len = stringLength(str);
    printf("Length of the string is: %d\n", len);

    return 0;
}