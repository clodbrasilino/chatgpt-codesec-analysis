#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

long long binaryToDecimal(const char *binary) {
    long long decimal = 0;
    int i = 0;

    if (binary == NULL || binary[0] == '\0') {
        return -1;
    }

    while (i < 64 && binary[i] != '\0') {
        if (binary[i] == '1') {
            decimal = (decimal << 1) | 1;
        } else if (binary[i] == '0') {
            decimal = decimal << 1;
        } else {
            return -1;
        }
        i++;
    }

    if (binary[i] != '\0') {
        return -1;
    }

    return decimal;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[128];
    long long result;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;

    printf("Enter a binary number: ");
    if (fgets(binary, sizeof(binary), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strnlen(binary, sizeof(binary));
    /* Possible weaknesses found:
     *  Assuming that condition 'len==0' is not redundant
     */
    if (len == 0 || (len == sizeof(binary) - 1 && binary[len - 1] != '\n')) {
        fprintf(stderr, "Invalid input\n");
        if (len == sizeof(binary) - 1 && binary[len - 1] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
        }
        return 1;
    }

    /* Possible weaknesses found:
     *  Condition 'len>0' is always true
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     */
    if (len > 0 && binary[len - 1] == '\n') {
        binary[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (len > 63) {
        fprintf(stderr, "Invalid binary number\n");
        return 1;
    }

    result = binaryToDecimal(binary);

    if (result == -1) {
        fprintf(stderr, "Invalid binary number\n");
        return 1;
    }

    printf("Decimal equivalent: %lld\n", result);

    return 0;
}