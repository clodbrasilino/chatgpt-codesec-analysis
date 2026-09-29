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

        size_t tempLen = strlen(temp);
        size_t needed = resultLen + tempLen + (resultLen > 0 ? 1 : 0) + 1;

        if (needed <= ipLen + 1) {
            if (resultLen > 0) {
                result[resultLen++] = '.';
            }
            memcpy(result + resultLen, temp, tempLen);
            resultLen += tempLen;
            result[resultLen] = '\0';
        }

        token = strtok_r(NULL, ".", &saveptr);
    }

    size_t copyLen = strnlen(result, size - 1);
    memcpy(ipAddress, result, copyLen);
    ipAddress[copyLen] = '\0';

    free(inputCopy);
    free(result);
}

int main(void) {
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