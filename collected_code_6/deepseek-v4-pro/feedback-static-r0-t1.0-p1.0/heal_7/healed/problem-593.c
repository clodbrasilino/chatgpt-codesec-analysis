#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INET_ADDRSTRLEN 16

void remove_leading_zeroes(char *ip) {
    if (ip == NULL || *ip == '\0') {
        return;
    }

    char result[INET_ADDRSTRLEN];
    size_t offset = 0;
    int first = 1;
    char *saveptr;

    char temp[INET_ADDRSTRLEN];
    size_t ip_len = strnlen(ip, INET_ADDRSTRLEN - 1);
    if (ip_len >= INET_ADDRSTRLEN || ip_len == 0) {
        return;
    }

    if (ip_len >= sizeof(temp)) {
        return;
    }

    memcpy(temp, ip, ip_len);
    temp[ip_len] = '\0';

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

        size_t len = strnlen(start, sizeof(result) - offset - 1);
        if (offset + len < sizeof(result) - 1) {
            memmove(result + offset, start, len);
            offset += len;
        } else {
            break;
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    if (offset >= sizeof(result)) {
        offset = sizeof(result) - 1;
    }
    result[offset] = '\0';

    size_t copy_len = strnlen(result, sizeof(result) - 1);
    if (copy_len >= INET_ADDRSTRLEN) {
        copy_len = INET_ADDRSTRLEN - 1;
    }
    memcpy(ip, result, copy_len);
    ip[copy_len] = '\0';
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