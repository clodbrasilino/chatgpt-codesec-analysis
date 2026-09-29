
#include <stdio.h>

int string_length(char* str) {
    int length = 0;
    while (*(str++)) {
       length++;
    }
    return length;
}

int main() {
    char str[] = "Hello, world!";
    int length = string_length(str);
    printf("Length of string: '%s' is %d\n", str, length);

    return 0;
}