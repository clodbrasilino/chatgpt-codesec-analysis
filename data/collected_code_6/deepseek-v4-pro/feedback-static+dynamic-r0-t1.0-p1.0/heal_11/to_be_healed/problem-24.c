#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static long long binaryToDecimal(const char *binary) {
    long long decimal = 0;

    if (binary == NULL || binary[0] == '\0') {
        return -1;
    }

    for (size_t i = 0; i < 64 && binary[i] != '\0'; i++) {
        if (binary[i] == '1') {
            decimal = (decimal << 1) | 1;
        } else if (binary[i] == '0') {
            decimal = decimal << 1;
        } else {
            return -1;
        }
    }

    return decimal;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[129] = {0};
    long long result;
    size_t len;
    size_t i;

    printf("Enter a binary number: ");
    if (fgets(binary, sizeof(binary), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(binary);

    if (len == 0 || binary[0] == '\n') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (binary[len - 1] != '\n') {
        if (len >= sizeof(binary) - 1) {
            fprintf(stderr, "Input too long\n");
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            return 1;
        }
    } else {
        binary[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    for (i = 0; i < len; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            fprintf(stderr, "Invalid binary number\n");
            return 1;
        }
    }

    if (len > 64) {
        fprintf(stderr, "Invalid binary number\n");
        return 1;
    }

    result = binaryToDecimal(binary);

    if (result == -1 && (len == 0 || binary[0] == '\0')) {
        fprintf(stderr, "Conversion error\n");
        return 1;
    }

    printf("Decimal equivalent: %lld\n", result);

    return 0;
}