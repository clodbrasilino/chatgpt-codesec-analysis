#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

long long octalToDecimal(const char *octalStr) {
    if (octalStr == NULL) {
        return -1;
    }

    size_t len = strlen(octalStr);
    if (len == 0) {
        return -1;
    }

    long long decimalNumber = 0;

    for (size_t i = 0; i < len; i++) {
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
    char input[64];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
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