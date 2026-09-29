#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return 0;
    }

    unsigned long long decimalValue = 0;

    for (size_t i = 0; binaryString[i] != '\0'; i++) {
        if (binaryString[i] == '1') {
            decimalValue = (decimalValue << 1) | 1;
        } else if (binaryString[i] == '0') {
            decimalValue = decimalValue << 1;
        } else {
            return 0;
        }
    }

    return decimalValue;
}

int main(void) {
    size_t bufferSize = 128;
    char *binaryString = (char *)malloc(bufferSize * sizeof(char));
    
    if (binaryString == NULL) {
        return 1;
    }

    if (fgets(binaryString, (int)bufferSize, stdin) == NULL) {
        free(binaryString);
        return 1;
    }

    binaryString[strcspn(binaryString, "\r\n")] = '\0';

    unsigned long long result = binaryToDecimal(binaryString);
    printf("%llu\n", result);

    free(binaryString);
    return 0;
}