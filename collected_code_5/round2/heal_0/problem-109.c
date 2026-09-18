#include <stdio.h>
#include <stdlib.h>
#include<string.h>


unsigned int binaryToDecimal(char *binaryString) {
    unsigned int decValue = 0, weight = 1;

    for(int i = strlen(binaryString) - 1; i >= 0; i--) {
        decValue += ((binaryString[i] - '0') * weight);
        weight *= 2;
    }

    return decValue;
}

int findOddRotations(char *binaryString) {
    int rotationCount = 0;
    size_t strLength = strlen(binaryString);
    char tempString[2 * strLength + 1];
    strcpy(tempString, binaryString);
    strcat(tempString, binaryString);

    for(int i = 0; i < strLength; i++) {
        char substring[strLength + 1];
        memcpy(substring, &tempString[i], strLength);
        substring[strLength] = '\0';

        if(binaryToDecimal(substring) % 2 != 0)
            rotationCount++;
    }

    return rotationCount;
}

int main() {
    char binaryString[] = "1011";
    printf("Count of rotations with odd decimal value : %d", findOddRotations(binaryString));
    return 0;
}