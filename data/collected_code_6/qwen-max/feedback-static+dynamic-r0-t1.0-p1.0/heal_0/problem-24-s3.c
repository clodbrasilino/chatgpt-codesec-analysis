#include <stdio.h>
#include <stdlib.h>

int binaryToDecimal(const char *binary) {
    int decimal = 0;
    int base = 1;
    int len = 0;

    while (binary[len] != '\0') {
        len++;
    }

    for (int i = len - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }

    return decimal;
}

int main() {
    const char *binary = "1101";
    int result = binaryToDecimal(binary);
    printf("%s in binary is %d in decimal\n", binary, result);
    return 0;
}