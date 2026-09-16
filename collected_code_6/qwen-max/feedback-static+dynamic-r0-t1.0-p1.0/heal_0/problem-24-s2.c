#include <stdio.h>
#include <stdlib.h>

int binary_to_decimal(const char *binary) {
    int decimal = 0;
    int length = 0;
    while (binary[length] != '\0') length++;
    for (int i = 0; i < length; i++) {
        if (binary[i] == '1') {
            decimal += 1 << (length - i - 1);
        } else if (binary[i] != '0') {
            return -1; // Invalid binary character
        }
    }
    return decimal;
}

int main() {
    const char *binary = "11010";
    int result = binary_to_decimal(binary);
    if (result != -1) {
        printf("Decimal: %d\n", result);
    } else {
        printf("Invalid binary input.\n");
    }
    return 0;
}