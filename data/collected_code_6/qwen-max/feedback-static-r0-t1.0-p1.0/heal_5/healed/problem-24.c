#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binary_to_decimal(const char *binary, size_t length) {
    int decimal = 0;
    for (size_t i = 0; i < length; ++i) {
        if (binary[i] == '1') {
            decimal += 1 << (length - i - 1);
        } else if (binary[i] != '0') {
            return -1;
        }
    }
    return decimal;
}

int main() {
    const char *binary = "1101";
    size_t length = strlen(binary);
    if (length > 0) {
        int result = binary_to_decimal(binary, length);
        if (result != -1) {
            printf("Decimal: %d\n", result);
        } else {
            printf("Invalid binary number\n");
        }
    } else {
        printf("Invalid input string\n");
    }
    return 0;
}