#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(binaryString);
    if (len == 0 || len > 63) {
        return -1;
    }

    long long decimalValue = 0;

    for (size_t i = 0; i < len; i++) {
        if (binaryString[i] != '0' && binaryString[i] != '1') {
            return -1; 
        }
        decimalValue = (decimalValue << 1) | (binaryString[i] - '0');
    }

    return decimalValue;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binaryInput[65];

    if (fgets(binaryInput, sizeof(binaryInput), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(binaryInput);
        if (len > 0 && binaryInput[len - 1] == '\n') {
            binaryInput[len - 1] = '\0';
        }

        long long result = binaryToDecimal(binaryInput);

        if (result != -1) {
            printf("%lld\n", result);
        } else {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}