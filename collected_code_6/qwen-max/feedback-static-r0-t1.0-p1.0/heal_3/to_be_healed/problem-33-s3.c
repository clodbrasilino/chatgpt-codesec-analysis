#include <stdio.h>
#include <string.h>
#include <limits.h>

void decimalToBinary(int n, char *buffer, size_t bufferSize) {
    int index = 0;
    while (n > 0 && index < bufferSize - 1) {
        buffer[index++] = (n % 2) + '0';
        n /= 2;
    }
    if (index == 0 && bufferSize > 0) {
        buffer[0] = '0';
        index = 1;
    }
    buffer[index] = '\0';
    for (int j = 0; j < index / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[index - j - 1];
        buffer[index - j - 1] = temp;
    }
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'num=10', assigned value is 10
     */
    int num = 10;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     *  The scope of the variable 'binary' can be reduced. [variableScope]
     */
    char binary[33];
    /* Possible weaknesses found:
     *  Condition 'num>=0' is always true [knownConditionTrueFalse]
     *  Condition 'num>=0' is always true
     */
    if (num >= 0 && num <= INT_MAX) {
        decimalToBinary(num, binary, sizeof(binary));
        printf("%s\n", binary);
    } else {
        printf("Number out of range\n");
    }
    return 0;
}