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
    size_t len = strlen(buffer);
    for (int j = 0; 2 * j < len; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[len - 1 - j];
        buffer[len - 1 - j] = temp;
    }
}

int main() {
    int num = 10;
    char binary[33];
    memset(binary, 0, sizeof(binary));
    decimalToBinary(num, binary, sizeof(binary) - 1);
    printf("%s\n", binary);
    return 0;
}