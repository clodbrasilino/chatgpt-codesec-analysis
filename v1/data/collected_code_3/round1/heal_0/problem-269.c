#include <stdio.h>

int findAscii(char c) {
    return (int)c;
}

int main() {
    char c;
    printf("Enter a character: ");
    scanf("%c", &c);
    printf("ASCII value of %c = %d", c, findAscii(c));
    return 0;
}