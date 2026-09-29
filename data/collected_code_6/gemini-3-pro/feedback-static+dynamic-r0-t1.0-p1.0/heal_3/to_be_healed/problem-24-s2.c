#include <stdio.h>
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binaryString[128];

    if (fgets(binaryString, sizeof(binaryString), stdin) == NULL) {
        return 1;
    }

    binaryString[strcspn(binaryString, "\r\n")] = '\0';

    unsigned long long result = binaryToDecimal(binaryString);
    printf("%llu\n", result);

    return 0;
}