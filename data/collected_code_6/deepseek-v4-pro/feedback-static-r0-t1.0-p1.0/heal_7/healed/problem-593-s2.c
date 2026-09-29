#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IP_ADDR_MAX_LEN 16

void remove_leading_zeros(char *ip) {
    if (ip == NULL) return;

    char result[IP_ADDR_MAX_LEN];
    char temp[IP_ADDR_MAX_LEN];
    char *token;
    char *saveptr;
    int first = 1;
    size_t result_len = 0;

    memset(result, 0, sizeof(result));
    memset(temp, 0, sizeof(temp));

    strncpy(temp, ip, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

    token = strtok_r(temp, ".", &saveptr);
    while (token != NULL && result_len < sizeof(result) - 1) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }

        if (!first) {
            if (result_len < sizeof(result) - 1) {
                result[result_len] = '.';
                result_len++;
                result[result_len] = '\0';
            }
        }

        size_t token_len = strnlen(start, sizeof(result) - result_len - 1);
        size_t remaining = sizeof(result) - result_len - 1;
        if (token_len > remaining) {
            token_len = remaining;
        }
        if (token_len > 0 && result_len + token_len < sizeof(result)) {
            memcpy(result + result_len, start, token_len);
            result_len += token_len;
            result[result_len] = '\0';
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    result[sizeof(result) - 1] = '\0';

    size_t result_str_len = strnlen(result, sizeof(result));
    size_t ip_max_size = IP_ADDR_MAX_LEN;
    size_t copy_len = result_str_len;
    if (copy_len >= ip_max_size) {
        copy_len = ip_max_size - 1;
    }
    memcpy(ip, result, copy_len);
    ip[copy_len] = '\0';
}

int main(void) {
    char ip1[IP_ADDR_MAX_LEN] = "192.168.001.001";
    remove_leading_zeros(ip1);
    printf("%s\n", ip1);

    char ip2[IP_ADDR_MAX_LEN] = "010.000.000.010";
    remove_leading_zeros(ip2);
    printf("%s\n", ip2);

    char ip3[IP_ADDR_MAX_LEN] = "0.0.0.0";
    remove_leading_zeros(ip3);
    printf("%s\n", ip3);

    char ip4[IP_ADDR_MAX_LEN] = "255.255.255.255";
    remove_leading_zeros(ip4);
    printf("%s\n", ip4);

    return 0;
}