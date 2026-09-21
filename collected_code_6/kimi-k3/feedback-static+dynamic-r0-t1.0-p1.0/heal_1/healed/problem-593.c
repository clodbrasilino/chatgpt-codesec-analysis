#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeLeadingZeros(char *ipAddress, size_t size) {
    char *token;
    char *saveptr;
    char *temp;
    char *result = (char *)malloc(strlen(ipAddress) + 1);
    if (result == NULL) {
        return;
    }
    result[0] = '\0';

    token = strtok_r(ipAddress, ".", &saveptr);
    while (token != NULL) {
        temp = token;
        while (*temp == '0') {
            temp++;
        }
        if (*temp == '\0') {
            temp--;
        }
        if (strlen(result) + strlen(temp) + 1 < strlen(ipAddress) + 1) {
            strcat(result, temp);
            strcat(result, ".");
        }
        token = strtok_r(NULL, ".", &saveptr);
    }

    if (strlen(result) > 0) {
        result[strlen(result) - 1] = '\0';
    }
    strncpy(ipAddress, result, size - 1);
    ipAddress[size - 1] = '\0';
    free(result);
}

int main() {
    char ipAddress[100];
    printf("Enter an IP address: ");
    if (fgets(ipAddress, sizeof(ipAddress), stdin) != NULL) {
        ipAddress[strcspn(ipAddress, "\n")] = '\0';
        removeLeadingZeros(ipAddress, sizeof(ipAddress));
        printf("IP address without leading zeros: %s\n", ipAddress);
    }
    return 0;
}