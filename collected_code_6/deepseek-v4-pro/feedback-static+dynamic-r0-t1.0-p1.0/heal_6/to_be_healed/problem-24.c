#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

long long binaryToDecimal(const char *binary) {
    long long decimal = 0;
    int i = 0;

    if (binary == NULL || binary[0] == '\0') {
        return -1;
    }

    while (i < 63 && binary[i] != '\0') {
        if (binary[i] == '1') {
            decimal = (decimal << 1) | 1;
        } else if (binary[i] == '0') {
            decimal = decimal << 1;
        } else {
            return -1;
        }
        i++;
    }

    if (binary[i] != '\0') {
        return -1;
    }

    return decimal;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[128] = {0};
    long long result;
    size_t len;

    printf("Enter a binary number: ");
    if (fgets(binary, sizeof(binary), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strnlen(binary, sizeof(binary));
    if (len > 0 && binary[len - 1] != '\n' && len == sizeof(binary) - 1) {
        fprintf(stderr, "Input too long\n");
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return 1;
    }

    if (len == 0 || binary[0] == '\n') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (binary[len - 1] == '\n') {
        binary[len - 1] = '\0';
        len--;
    }

    if (len > 63) {
        fprintf(stderr, "Invalid binary number\n");
        return 1;
    }

    result = binaryToDecimal(binary);

    if (result == -1) {
        int valid = 1;
        for (size_t j = 0; j < len; j++) {
            if (binary[j] != '0' && binary[j] != '1') {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            fprintf(stderr, "Invalid binary number\n");
            return 1;
        }
    }

    printf("Decimal equivalent: %lld\n", result);

    return 0;
}