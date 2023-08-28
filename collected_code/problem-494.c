#include<stdio.h>

int binaryToDecimal(int binary[], int n) {
    int decimal = 0;

    for (int i = 0; i < n; i++) {
        decimal = decimal * 2 + binary[i];
    }

    return decimal;
}

int main() {
    int binary[] = {1, 0, 1, 0, 1};
    int n = sizeof(binary) / sizeof(binary[0]);

    int decimal = binaryToDecimal(binary, n);

    printf("Decimal value: %d\n", decimal);

    return 0;
}