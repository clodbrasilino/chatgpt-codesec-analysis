#include <stdio.h>

int findStringLength(char* str) {
    if(str == NULL) {
        return 0;
    }
    
    int length = 0;

    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

int main() {
    char str[] = "Hello, world!";
    int length = findStringLength(str);
    printf("Length of the string is: %d\n", length);
    return 0;
}