#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return -1;
    }

    long long decimalValue = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = strlen(binaryString);

    for (int i = 0; i < length; i++) {
        if (binaryString[i] != '0' && binaryString[i] != '1') {
            return -1; 
        }
        
        int bit = binaryString[i] - '0';
        decimalValue = (decimalValue << 1) | bit;
    }

    return decimalValue;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binaryString[65]; 

    if (fgets(binaryString, sizeof(binaryString), stdin) != NULL) {
        binaryString[strcspn(binaryString, "\n")] = '\0';

        long long result = binaryToDecimal(binaryString);

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