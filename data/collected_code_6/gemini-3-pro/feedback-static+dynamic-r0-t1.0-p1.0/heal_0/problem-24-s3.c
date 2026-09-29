#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return -1;
    }

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
    char binaryInput[65];

    if (fgets(binaryInput, sizeof(binaryInput), stdin) != NULL) {
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