#include <stdio.h>
#include <string.h>
#include <math.h>

unsigned long long binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return 0;
    }

    unsigned long long decimalValue = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(binaryString);

    for (size_t i = 0; i < length; i++) {
        if (binaryString[i] == '1') {
            decimalValue += (1ULL << (length - 1 - i));
        } else if (binaryString[i] != '0') {
            return 0;
        }
    }

    return decimalValue;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binaryString[65];

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%64s", binaryString) != 1) {
        return 1;
    }

    unsigned long long result = binaryToDecimal(binaryString);
    printf("%llu\n", result);

    return 0;
}