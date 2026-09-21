#define _POSIX_C_SOURCE 200809L
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
            decimalValue = (decimalValue << 1) | 1ULL;
        } else if (binaryString[i] == '0') {
            decimalValue = decimalValue << 1;
        } else {
            return 0;
        }
    }

    return decimalValue;
}

int main(void) {
    char *binaryString = NULL;
    size_t len = 0;

    if (getline(&binaryString, &len, stdin) == -1) {
        free(binaryString);
        return 1;
    }

    binaryString[strcspn(binaryString, "\r\n")] = '\0';

    unsigned long long result = binaryToDecimal(binaryString);
    printf("%llu\n", result);

    free(binaryString);
    return 0;
}