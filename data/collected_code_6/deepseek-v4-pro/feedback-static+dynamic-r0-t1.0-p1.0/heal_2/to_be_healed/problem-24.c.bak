#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

long long binaryToDecimal(const char *binary, int *error) {
    long long decimal = 0;
    int length = strlen(binary);
    int i;

    *error = 0;

    if (length > 63) {
        *error = 1;
        return 0;
    }

    for (i = 0; i < length; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            *error = 1;
            return 0;
        }

        if (binary[i] == '1') {
            int shift = length - 1 - i;
            /* Possible weaknesses found:
             *  Assuming that condition 'shift>=(int)(sizeof(long long)*8-1)' is not redundant
             */
            if (shift >= (int)(sizeof(long long) * 8 - 1)) {
                if (decimal > 0 || binary[0] == '0') {
                    *error = 1;
                    return 0;
                }
            }

            /* Possible weaknesses found:
             *  Shifting signed 64-bit value by 63 bits is implementation-defined behaviour. See condition at line 27. [shiftTooManyBitsSigned]
             *  Shift
             */
            long long addend = 1LL << shift;

            if (addend < 0 || decimal > LLONG_MAX - addend) {
                *error = 1;
                return 0;
            }

            decimal += addend;
        }
    }

    return decimal;
}

int main(void) {
    char binary[72];
    long long result;
    int error;

    printf("Enter a binary number: ");
    if (fgets(binary, sizeof(binary), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    size_t len = strlen(binary);
    if (len > 0 && binary[len - 1] == '\n') {
        binary[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    result = binaryToDecimal(binary, &error);

    if (error) {
        fprintf(stderr, "Invalid binary number or out of range\n");
        return 1;
    }

    printf("Decimal equivalent: %lld\n", result);

    return 0;
}