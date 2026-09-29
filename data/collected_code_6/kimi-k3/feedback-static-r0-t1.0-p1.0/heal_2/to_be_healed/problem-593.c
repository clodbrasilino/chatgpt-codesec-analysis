#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeLeadingZeros(char *ipAddress, size_t ipAddressSize) {
    if (ipAddress == NULL || ipAddressSize == 0) {
        return;
    }

    size_t ipLength = strnlen(ipAddress, ipAddressSize);
    if (ipLength == ipAddressSize) {
        return;
    }

    char *result = (char *)malloc(ipLength + 1);
    if (result == NULL) {
        return;
    }
    result[0] = '\0';

    size_t resultLen = 0;
    size_t resultCapacity = ipLength + 1;

    char *saveptr;
    char *token = strtok_r(ipAddress, ".", &saveptr);

    while (token != NULL) {
        char *temp = token;
        while (*temp == '0') {
            temp++;
        }
        if (*temp == '\0') {
            temp--;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t tokenLen = strlen(temp);
        size_t needed = resultLen + tokenLen + 2;

        if (needed > resultCapacity) {
            size_t newCapacity = resultCapacity * 2;
            while (newCapacity < needed) {
                newCapacity *= 2;
            }
            char *newResult = (char *)realloc(result, newCapacity);
            if (newResult == NULL) {
                free(result);
                return;
            }
            result = newResult;
            resultCapacity = newCapacity;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + resultLen, temp, tokenLen);
        resultLen += tokenLen;
        result[resultLen++] = '.';
        result[resultLen] = '\0';

        token = strtok_r(NULL, ".", &saveptr);
    }

    if (resultLen > 0) {
        result[resultLen - 1] = '\0';
        resultLen--;
    }

    if (resultLen < ipAddressSize) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ipAddress, result, resultLen + 1);
    }

    free(result);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ipAddress[100];

    printf("Enter an IP address: ");

    if (fgets(ipAddress, sizeof(ipAddress), stdin) == NULL) {
        return 1;
    }

    size_t newlinePos = strcspn(ipAddress, "\n");
    ipAddress[newlinePos] = '\0';

    removeLeadingZeros(ipAddress, sizeof(ipAddress));

    printf("IP address without leading zeros: %s\n", ipAddress);

    return 0;
}