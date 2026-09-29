#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long octalToDecimal(const char *octalStr) {
    if (octalStr == NULL || *octalStr == '\0') {
        return -1;
    }

    long long decimalNumber = 0;

    for (int i = 0; octalStr[i] != '\0'; i++) {
        if (octalStr[i] < '0' || octalStr[i] > '7') {
            return -1;
        }
        decimalNumber = decimalNumber * 8 + (octalStr[i] - '0');
    }

    return decimalNumber;
}

int main(void) {
    size_t bufsize = 64;
    char *input = (char *)malloc(bufsize);
    
    if (input == NULL) {
        return EXIT_FAILURE;
    }
    
    if (fgets(input, bufsize, stdin) != NULL) {
        char *newline = strchr(input, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        long long result = octalToDecimal(input);
        
        if (result != -1) {
            printf("%lld\n", result);
            free(input);
            return EXIT_SUCCESS;
        }
    }

    free(input);
    return EXIT_FAILURE;
}