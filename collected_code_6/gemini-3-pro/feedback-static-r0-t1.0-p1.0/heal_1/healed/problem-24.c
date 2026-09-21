#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return -1;
    }

    long long decimalValue = 0;
    size_t length = strnlen(binaryString, 65);

    for (size_t i = 0; i < length; i++) {
        if (binaryString[i] != '0' && binaryString[i] != '1') {
            return -1; 
        }
        
        int bit = binaryString[i] - '0';
        decimalValue = (decimalValue << 1) | bit;
    }

    return decimalValue;
}

int main(void) {
    size_t buffer_size = 65;
    char *binaryString = (char *)malloc(buffer_size);

    if (binaryString == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return EXIT_FAILURE;
    }

    if (fgets(binaryString, buffer_size, stdin) != NULL) {
        binaryString[strcspn(binaryString, "\n")] = '\0';

        long long result = binaryToDecimal(binaryString);

        if (result != -1) {
            printf("%lld\n", result);
        } else {
            fprintf(stderr, "Invalid input\n");
            free(binaryString);
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Error reading input\n");
        free(binaryString);
        return EXIT_FAILURE;
    }

    free(binaryString);
    return EXIT_SUCCESS;
}