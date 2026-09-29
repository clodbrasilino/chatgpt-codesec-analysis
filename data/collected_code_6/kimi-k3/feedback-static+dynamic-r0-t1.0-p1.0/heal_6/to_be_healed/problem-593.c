#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeLeadingZeros(char *ipAddress, size_t size) {
    if (ipAddress == NULL || size == 0) {
        return;
    }

    size_t ipLen = strnlen(ipAddress, size);
    if (ipLen == 0 || ipLen >= size) {
        return;
    }

    char *result = (char *)malloc(ipLen + 1);
    if (result == NULL) {
        return;
    }
    result[0] = '\0';

    char *inputCopy = (char *)malloc(ipLen + 1);
    if (inputCopy == NULL) {
        free(result);
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(inputCopy, ipAddress, ipLen);
    inputCopy[ipLen] = '\0';

    size_t resultLen = 0;
    char *saveptr = NULL;
    char *token = strtok_r(inputCopy, ".", &saveptr);

    while (token != NULL) {
        char *temp = token;
        while (*temp == '0' && *(temp + 1) != '\0') {
            temp++;
        }

        size_t tempLen = strnlen(temp, ipLen + 1);
        size_t needed = resultLen + tempLen + (resultLen > 0 ? 1 : 0) + 1;

        if (needed <= ipLen + 1) {
            if (resultLen > 0) {
                result[resultLen++] = '.';
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + resultLen, temp, tempLen);
            resultLen += tempLen;
            result[resultLen] = '\0';
        }

        token = strtok_r(NULL, ".", &saveptr);
    }

    size_t copyLen = strnlen(result, size - 1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(ipAddress, result, copyLen);
    ipAddress[copyLen] = '\0';

    free(inputCopy);
    free(result);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ipAddress[100];

    printf("Enter an IP address: ");
    if (fgets(ipAddress, sizeof(ipAddress), stdin) != NULL) {
        size_t len = strcspn(ipAddress, "\n");
        ipAddress[len] = '\0';

        if (len > 0) {
            removeLeadingZeros(ipAddress, sizeof(ipAddress));
            printf("IP address without leading zeros: %s\n", ipAddress);
        }
    }

    return 0;
}