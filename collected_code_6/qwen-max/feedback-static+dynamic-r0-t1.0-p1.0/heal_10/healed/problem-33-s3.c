#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseString(char *str, size_t length) {
    for (size_t i = 0; 2 * i < length; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

void decimalToBinary(int n, char *buffer, size_t bufferSize) {
    if (n < 0 || bufferSize <= 1) return;
    int i = 0;
    while (n > 0 && i < bufferSize - 2) {
        buffer[i++] = (n % 2) + '0';
        n /= 2;
    }
    buffer[i] = '\0';
    reverseString(buffer, i);
}

int main() {
    int num = 10;
    char binary[33] = {0};
    decimalToBinary(num, binary, sizeof(binary));
    printf("%s\n", binary);
    return 0;
}