#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

long long binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return -1;
    }

    unsigned long long decimalValue = 0;
    size_t i = 0;

    while (binaryString[i] != '\0') {
        if (i >= 63) {
            return -1;
        }
        
        if (binaryString[i] != '0' && binaryString[i] != '1') {
            return -1; 
        }
        
        unsigned int bit = binaryString[i] - '0';
        decimalValue = (decimalValue << 1) | bit;
        i++;
    }

    if (i == 0) {
        return -1;
    }

    if (decimalValue > LLONG_MAX) {
        return -1;
    }

    return (long long)decimalValue;
}

int main(void) {
    char binaryString[128]; 

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