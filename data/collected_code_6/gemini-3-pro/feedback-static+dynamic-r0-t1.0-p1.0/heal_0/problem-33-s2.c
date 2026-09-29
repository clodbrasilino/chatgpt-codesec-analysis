#include <stdio.h>
#include <stdlib.h>

char* decimalToBinary(int decimalNum) {
    if (decimalNum == 0) {
        char* zeroStr = (char*)malloc(2 * sizeof(char));
        if (zeroStr == NULL) {
            return NULL;
        }
        zeroStr[0] = '0';
        zeroStr[1] = '\0';
        return zeroStr;
    }

    int temp = decimalNum;
    int numBits = 0;
    while (temp > 0) {
        temp /= 2;
        numBits++;
    }

    char* binaryStr = (char*)malloc((numBits + 1) * sizeof(char));
    if (binaryStr == NULL) {
        return NULL;
    }

    binaryStr[numBits] = '\0';
    temp = decimalNum;
    for (int i = numBits - 1; i >= 0; i--) {
        binaryStr[i] = (temp % 2) + '0';
        temp /= 2;
    }

    return binaryStr;
}

int main(void) {
    int decimalNum;

    if (scanf("%d", &decimalNum) != 1) {
        return 1;
    }

    if (decimalNum < 0) {
        return 1;
    }

    char* binaryStr = decimalToBinary(decimalNum);
    if (binaryStr == NULL) {
        return 1;
    }

    printf("%s\n", binaryStr);

    free(binaryStr);

    return 0;
}