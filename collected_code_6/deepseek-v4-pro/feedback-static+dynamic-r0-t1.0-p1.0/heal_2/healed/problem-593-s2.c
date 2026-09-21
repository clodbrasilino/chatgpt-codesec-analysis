#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int remove_leading_zeros(char *ip, size_t ip_size) {
    if (ip == NULL || ip_size == 0) return -1;

    char result[16];
    char temp[16];
    char *token;
    char *saveptr;
    int first = 1;
    size_t result_len = 0;

    memset(result, 0, sizeof(result));
    memset(temp, 0, sizeof(temp));

    if (strlen(ip) >= sizeof(temp)) {
        return -1;
    }
    strcpy(temp, ip);

    token = strtok_r(temp, ".", &saveptr);
    while (token != NULL) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }

        if (!first) {
            if (result_len < sizeof(result) - 1) {
                result[result_len] = '.';
                result_len++;
                result[result_len] = '\0';
            } else {
                return -1;
            }
        }

        size_t seg_len = strlen(start);
        if (result_len + seg_len >= sizeof(result)) {
            return -1;
        }
        memcpy(result + result_len, start, seg_len);
        result_len += seg_len;
        result[result_len] = '\0';

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    size_t copy_len = strlen(result);
    if (copy_len >= ip_size) {
        copy_len = ip_size - 1;
    }
    memmove(ip, result, copy_len);
    ip[copy_len] = '\0';

    return 0;
}

int main(void) {
    char ip1[16] = "192.168.001.001";
    remove_leading_zeros(ip1, sizeof(ip1));
    printf("%s\n", ip1);

    char ip2[16] = "010.000.000.010";
    remove_leading_zeros(ip2, sizeof(ip2));
    printf("%s\n", ip2);

    char ip3[16] = "0.0.0.0";
    remove_leading_zeros(ip3, sizeof(ip3));
    printf("%s\n", ip3);

    char ip4[16] = "255.255.255.255";
    remove_leading_zeros(ip4, sizeof(ip4));
    printf("%s\n", ip4);

    return 0;
}