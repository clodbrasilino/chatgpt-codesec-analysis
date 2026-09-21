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
    size_t size = 64;
    char *input = (char *)malloc(size * sizeof(char));
    
    if (input == NULL) {
        return EXIT_FAILURE;
    }
    
    if (fgets(input, size, stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        
        if (input[0] == '\0') {
            free(input);
            return EXIT_FAILURE;
        }

        long long result = octalToDecimal(input);
        
        if (result != -1) {
            printf("%lld\n", result);
            free(input);
            return EXIT_SUCCESS;
        } else {
            free(input);
            return EXIT_FAILURE;
        }
    }

    free(input);
    return EXIT_FAILURE;
}