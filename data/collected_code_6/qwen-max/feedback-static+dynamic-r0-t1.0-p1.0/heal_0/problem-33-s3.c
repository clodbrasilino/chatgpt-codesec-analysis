#include <stdio.h>
#include <string.h>

void decimalToBinary(int n, char *buffer) {
    int i = 0;
    while (n > 0) {
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
    char binary[33] = "";
    if (num >= 0 && num <= 2147483647) {
        decimalToBinary(num, binary);
        printf("%s\n", binary);
    } else {
        printf("Number out of range\n");
    }
    return 0;
}