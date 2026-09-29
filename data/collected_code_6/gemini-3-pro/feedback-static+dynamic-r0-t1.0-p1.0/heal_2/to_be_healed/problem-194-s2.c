#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

long long octalToDecimal(const char *octalStr) {
    if (octalStr == NULL || octalStr[0] == '\0') {
        return -1;
    }

    long long decimalNumber = 0;

    for (size_t i = 0; octalStr[i] != '\0'; i++) {
        if (octalStr[i] < '0' || octalStr[i] > '7') {
            return -1;
        }
        
        int digit = octalStr[i] - '0';
        
        if (decimalNumber > (LLONG_MAX - digit) / 8) {
            return -1;
        }
        
        decimalNumber = decimalNumber * 8 + digit;
    }

    return decimalNumber;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        
        if (input[0] == '\0') {
            return EXIT_FAILURE;
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