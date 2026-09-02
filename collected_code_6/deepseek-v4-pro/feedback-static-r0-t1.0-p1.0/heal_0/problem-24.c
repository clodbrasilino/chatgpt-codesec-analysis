#include <stdio.h>
#include <string.h>
#include <math.h>

long long binaryToDecimal(const char *binary) {
    long long decimal = 0;
    int length = strlen(binary);
    int i;

    for (i = 0; i < length; i++) {
        if (binary[i] == '1') {
            decimal += (long long)pow(2, length - 1 - i);
        } else if (binary[i] != '0') {
            return -1;
        }
    }

    return decimal;
}

int main(void) {
    char binary[65];
    long long result;

    printf("Enter a binary number: ");
    if (fgets(binary, sizeof(binary), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    size_t len = strlen(binary);
    if (len > 0 && binary[len - 1] == '\n') {
        binary[len - 1] = '\0';
    }

    if (binary[0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    result = binaryToDecimal(binary);

    if (result == -1) {
        fprintf(stderr, "Invalid binary number\n");
        return 1;
    }

    printf("Decimal equivalent: %lld\n", result);

    return 0;
}