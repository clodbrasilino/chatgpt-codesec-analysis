#include <stdio.h>

int stringLength(char* str) {
    int length = 0;
    while(*str != '\0') {
        length++;
        str++;
    }
    return length;
}

int main() {
    char str[] = "Hello, World!";
    int length = stringLength(str);
    printf("Length of the string is: %d\n", length);
    return 0;
}