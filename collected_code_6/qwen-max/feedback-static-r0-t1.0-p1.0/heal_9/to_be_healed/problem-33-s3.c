#include <stdio.h>
#include <string.h>
#include <limits.h>

void decimalToBinary(int n, char *buffer, size_t bufferSize) {
    if (bufferSize == 0) return;
    int index = 0;
    while (n > 0 && index < bufferSize - 1) {
        buffer[index++] = (n % 2) + '0';
        n /= 2;
    }
    if (index == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
    } else {
        buffer[index] = '\0';
        for (int j = 0; j < index / 2; j++) {
            char temp = buffer[j];
            buffer[j] = buffer[index - j - 1];
            buffer[index - j - 1] = temp;
        }
    }
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (num >= 0 && num <= INT_MAX) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char binary[33];
        decimalToBinary(num, binary, sizeof(binary));
        printf("%s\n", binary);
    } else {
        printf("Number out of range\n");
    }
    return 0;
}