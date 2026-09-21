#include <stdio.h>
#include <stdlib.h>

void decimalToOctal(int decimal, char *octalStr, size_t size) {
    if (octalStr == NULL || size == 0) {
        return;
    }
    
    if (decimal == 0) {
        if (size < 2) {
            octalStr[0] = '\0';
            return;
        }
        octalStr[0] = '0';
        octalStr[1] = '\0';
        return;
    }
    
    int temp = decimal < 0 ? -decimal : decimal;
    int isNegative = decimal < 0;
    int octalDigits[32];
    int index = 0;
    
    while (temp > 0) {
        octalDigits[index++] = temp % 8;
        temp /= 8;
    }
    
    size_t requiredLength = (size_t)index + (isNegative ? 2 : 1);
    if (requiredLength > size) {
        octalStr[0] = '\0';
        return;
    }
    
    size_t pos = 0;
    if (isNegative) {
        octalStr[pos++] = '-';
    }
    
    for (int i = index - 1; i >= 0; i--) {
        octalStr[pos++] = '0' + octalDigits[i];
    }
    
    octalStr[pos] = '\0';
}

int main(void) {
    int numbers[] = {0, 8, 64, 100, -8, 123456, -255};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[33];
    
    for (size_t i = 0; i < count; i++) {
        decimalToOctal(numbers[i], buffer, sizeof(buffer));
        printf("Decimal: %d -> Octal: %s\n", numbers[i], buffer);
    }
    
    return 0;
}