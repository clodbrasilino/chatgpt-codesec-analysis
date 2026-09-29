#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INET_ADDRSTRLEN 16

void remove_leading_zeroes(char *ip) {
    if (ip == NULL || *ip == '\0') {
        return;
    }

    char result[INET_ADDRSTRLEN] = {0};
    size_t offset = 0;
    int first = 1;
    char *saveptr;
    char temp[INET_ADDRSTRLEN];

    temp[0] = '\0';
    strncat(temp, ip, sizeof(temp) - 1);

    char *token = strtok_r(temp, ".", &saveptr);

    while (token != NULL) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }

        if (!first) {
            if (offset < sizeof(result) - 1) {
                result[offset++] = '.';
            } else {
                break;
            }
        }

        size_t len = strnlen(start, sizeof(result) - offset);
        if (offset + len < sizeof(result)) {
            memmove(result + offset, start, len);
            offset += len;
        } else {
            break;
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    result[offset] = '\0';

    size_t result_len = strnlen(result, INET_ADDRSTRLEN);
    if (result_len < INET_ADDRSTRLEN) {
        strncpy(ip, result, INET_ADDRSTRLEN);
        ip[INET_ADDRSTRLEN - 1] = '\0';
    }
}

int main(void) {
    char ip1[INET_ADDRSTRLEN] = "192.168.001.001";
    char ip2[INET_ADDRSTRLEN] = "010.000.000.001";
    char ip3[INET_ADDRSTRLEN] = "000.000.000.000";
    char ip4[INET_ADDRSTRLEN] = "255.255.255.255";
    char ip5[INET_ADDRSTRLEN] = "001.002.003.004";

    remove_leading_zeroes(ip1);
    remove_leading_zeroes(ip2);
    remove_leading_zeroes(ip3);
    remove_leading_zeroes(ip4);
    remove_leading_zeroes(ip5);

    printf("%s\n", ip1);
    printf("%s\n", ip2);
    printf("%s\n", ip3);
    printf("%s\n", ip4);
    printf("%s\n", ip5);

    return 0;
}