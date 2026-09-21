#include <stdio.h>
#include <string.h>
#include <limits.h>

void decimalToBinary(int n, char *buffer, int bufferSize) {
    if (n < 0 || n > INT_MAX || bufferSize < 2) return;
    int i = 0;
    while (n > 0 && i < bufferSize - 1) {
        buffer[i++] = (n % 2) + '0';
        n /= 2;
    }
    buffer[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

int main() {
    int num = 10;
    char binary[33];
    decimalToBinary(num, binary, sizeof(binary));
    printf("%s\n", binary);
    return 0;
}