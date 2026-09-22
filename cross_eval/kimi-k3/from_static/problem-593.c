#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool isValidIPv4Segment(const char *segment) {
    if (segment == NULL || *segment == '\0') {
        return false;
    }
    
    size_t len = strlen(segment);
    if (len > 3) {
        return false;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)segment[i])) {
            return false;
        }
    }
    
    int value = atoi(segment);
    if (value < 0 || value > 255) {
        return false;
    }
    
    return true;
}

bool removeLeadingZeros(char *ipAddress, size_t ipAddressSize) {
    if (ipAddress == NULL || ipAddressSize == 0) {
        return false;
    }

    size_t ipLength = strnlen(ipAddress, ipAddressSize);
    if (ipLength == ipAddressSize) {
        return false;
    }

    char *result = (char *)malloc(ipLength + 1);
    if (result == NULL) {
        return false;
    }
    result[0] = '\0';

    size_t resultLen = 0;
    size_t resultCapacity = ipLength + 1;
    int segmentCount = 0;

    char *saveptr;
    char *token = strtok_r(ipAddress, ".", &saveptr);

    while (token != NULL) {
        if (!isValidIPv4Segment(token)) {
            free(result);
            return false;
        }
        
        segmentCount++;
        if (segmentCount > 4) {
            free(result);
            return false;
        }

        char *temp = token;
        while (*temp == '0') {
            temp++;
        }
        if (*temp == '\0') {
            temp--;
        }

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
                return false;
            }
            result = newResult;
            resultCapacity = newCapacity;
        }

        if (resultLen + tokenLen + 2 <= resultCapacity) {
            memcpy(result + resultLen, temp, tokenLen);
            resultLen += tokenLen;
            result[resultLen++] = '.';
            result[resultLen] = '\0';
        } else {
            free(result);
            return false;
        }

        token = strtok_r(NULL, ".", &saveptr);
    }

    if (segmentCount != 4) {
        free(result);
        return false;
    }

    if (resultLen > 0) {
        result[resultLen - 1] = '\0';
        resultLen--;
    }

    if (resultLen + 1 <= ipAddressSize) {
        memcpy(ipAddress, result, resultLen + 1);
        free(result);
        return true;
    }

    free(result);
    return false;
}

int main(void) {
    char ipAddress[100];

    printf("Enter an IP address: ");

    if (fgets(ipAddress, sizeof(ipAddress), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    size_t newlinePos = strcspn(ipAddress, "\n");
    ipAddress[newlinePos] = '\0';

    if (strlen(ipAddress) == 0) {
        fprintf(stderr, "Empty input\n");
        return 1;
    }

    if (!removeLeadingZeros(ipAddress, sizeof(ipAddress))) {
        fprintf(stderr, "Invalid IP address format\n");
        return 1;
    }

    printf("IP address without leading zeros: %s\n", ipAddress);

    return 0;
}