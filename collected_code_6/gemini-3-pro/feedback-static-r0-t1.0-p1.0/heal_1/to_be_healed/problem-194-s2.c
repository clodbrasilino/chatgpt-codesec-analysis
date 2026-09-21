#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

long long octalToDecimal(const char *octalStr) {
    if (octalStr == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(octalStr);
    if (len == 0) {
        return -1;
    }

    long long decimalNumber = 0;
    int power = 0;

    for (int i = len - 1; i >= 0; i--) {
        if (!isdigit((unsigned char)octalStr[i]) || octalStr[i] == '8' || octalStr[i] == '9') {
            return -1;
        }
        int digit = octalStr[i] - '0';
        decimalNumber += digit * (long long)pow(8, power);
        power++;
    }

    return decimalNumber;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        long long result = octalToDecimal(input);
        
        if (result != -1) {
            printf("%lld\n", result);
            return EXIT_SUCCESS;
        } else {
            return EXIT_FAILURE;
        }
    }

    return EXIT_FAILURE;
}