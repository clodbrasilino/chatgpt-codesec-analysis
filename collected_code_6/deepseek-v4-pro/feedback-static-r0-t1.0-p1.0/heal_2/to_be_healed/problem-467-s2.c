#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

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
    
    unsigned int temp;
    int isNegative = 0;
    
    if (decimal < 0) {
        temp = (unsigned int)(-(decimal + 1)) + 1;
        isNegative = 1;
    } else {
        temp = (unsigned int)decimal;
    }
    
    int octalDigits[32];
    int index = 0;
    
    while (temp > 0) {
        octalDigits[index++] = (int)(temp % 8);
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
        octalStr[pos++] = (char)('0' + octalDigits[i]);
    }
    
    octalStr[pos] = '\0';
}

int main(void) {
    /* Possible weaknesses found:
     *  'INT_MIN' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'INT_MIN'
     */
    int numbers[] = {0, 8, 64, 100, -8, 123456, -255, INT_MIN};
    /* Possible weaknesses found:
     *  invalid application of 'sizeof' to an incomplete type 'int[]'
     */
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[33];
    
    for (size_t i = 0; i < count; i++) {
        memset(buffer, 0, sizeof(buffer));
        decimalToOctal(numbers[i], buffer, sizeof(buffer));
        printf("Decimal: %d -> Octal: %s\n", numbers[i], buffer);
    }
    
    return 0;
}