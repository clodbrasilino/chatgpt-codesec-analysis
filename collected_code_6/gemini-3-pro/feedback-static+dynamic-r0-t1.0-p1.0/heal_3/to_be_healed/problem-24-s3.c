#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return -1;
    }

    long long decimalValue = 0;
    size_t len = 0;

    for (const char *p = binaryString; *p != '\0'; p++) {
        if (len >= 63) {
            return -1;
        }
        if (*p != '0' && *p != '1') {
            return -1;
        }
        decimalValue = (decimalValue << 1) | (*p - '0');
        len++;
    }

    if (len == 0) {
        return -1;
    }

    return decimalValue;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binaryInput[128];

    if (fgets(binaryInput, sizeof(binaryInput), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    binaryInput[strcspn(binaryInput, "\r\n")] = '\0';

    long long result = binaryToDecimal(binaryInput);

    if (result != -1) {
        printf("%lld\n", result);
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}