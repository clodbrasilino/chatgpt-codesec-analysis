#include <stdio.h>
#include <string.h>
#include <limits.h>

void decimalToBinary(int n, char *buffer) {
    int i = 0;
    if (n == 0 || n == -INT_MAX) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    int temp = n < 0 ? -n : n;
    while (temp != 0) {
        buffer[i++] = (temp % 2) + '0';
        temp /= 2;
    }
    if (n < 0) {
        buffer[i++] = '-';
    }
    buffer[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char t = buffer[j];
        buffer[j] = buffer[i - j - (n < 0 ? 1 : 0)];
        buffer[i - j - (n < 0 ? 1 : 0)] = t;
    }
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'num=10', assigned value is 10
     */
    int num = 10;
    /* Possible weaknesses found:
     *  Condition 'num>=0' is always true [knownConditionTrueFalse]
     *  Condition 'num>=0' is always true
     */
    if (num >= 0 && num <= INT_MAX) {
        char binary[33];
        decimalToBinary(num, binary);
        printf("%s\n", binary);
    } else {
        printf("Number out of range\n");
    }
    return 0;
}