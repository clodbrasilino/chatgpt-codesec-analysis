#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void removeLeadingZeros(char *ipAddress, size_t size) {
    if (ipAddress == NULL || size == 0) {
        return;
    }

    size_t ipLen = strnlen(ipAddress, size);
    if (ipLen == 0 || ipLen >= size) {
        return;
    }

    char *result = (char *)calloc(ipLen + 1, sizeof(char));
    if (result == NULL) {
        return;
    }

    char *inputCopy = (char *)calloc(ipLen + 1, sizeof(char));
    if (inputCopy == NULL) {
        free(result);
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(inputCopy, ipAddress, ipLen);
    inputCopy[ipLen] = '\0';

    size_t resultLen = 0;
    char *saveptr = NULL;
    char *token = strtok_r(inputCopy, ".", &saveptr);

    while (token != NULL) {
        char *temp = token;
        while (*temp == '0' && *(temp + 1) != '\0') {
            temp++;
        }

        size_t tempLen = strnlen(temp, ipLen);
        size_t needed = resultLen + tempLen + (resultLen > 0 ? 1 : 0) + 1;

        if (needed <= ipLen + 1) {
            if (resultLen > 0) {
                result[resultLen++] = '.';
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result + resultLen, temp, tempLen);
            resultLen += tempLen;
            result[resultLen] = '\0';
        }

        token = strtok_r(NULL, ".", &saveptr);
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(ipAddress, result, size - 1);
    ipAddress[size - 1] = '\0';

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

        if (len > 0 && len < sizeof(ipAddress)) {
            removeLeadingZeros(ipAddress, sizeof(ipAddress));
            printf("IP address without leading zeros: %s\n", ipAddress);
        }
    }

    return 0;
}