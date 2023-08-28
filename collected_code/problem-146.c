#include <stdio.h>

int findAsciiValueOfString(char *str) {
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        sum += (int)str[i];
    }
    return sum;
}

int main() {
    char str[] = "Hello World!";
    int asciiSum = findAsciiValueOfString(str);
    printf("ASCII value of the characters in the string: %d\n", asciiSum);
    return 0;
}