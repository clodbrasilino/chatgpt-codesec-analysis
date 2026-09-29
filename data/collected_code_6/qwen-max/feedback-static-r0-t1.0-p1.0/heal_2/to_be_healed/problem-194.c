#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int octalToDecimal(const char *octal, size_t len) {
    int decimal = 0, base = 1;

    for (int i = len - 1; i >= 0; --i) {
        if (isdigit(octal[i]) && octal[i] < '8') {
            decimal += (octal[i] - '0') * base;
            base *= 8;
        } else {
            return -1; // Invalid octal digit
        }
    }
    return decimal;
}

int main() {
    const char *octal = "123";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(octal);
    int decimal = octalToDecimal(octal, len);

    if (decimal != -1) {
        printf("Octal: %s, Decimal: %d\n", octal, decimal);
    } else {
        printf("Invalid octal number: %s\n", octal);
    }

    return 0;
}