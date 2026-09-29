#include <stdio.h>
#include <string.h>
#include <limits.h>

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