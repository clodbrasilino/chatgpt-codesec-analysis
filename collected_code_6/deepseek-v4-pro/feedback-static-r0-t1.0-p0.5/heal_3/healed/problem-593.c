#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IP_LEN 16

void remove_leading_zeroes(char *ip, size_t ip_size) {
    if (ip == NULL || ip_size == 0 || ip_size > MAX_IP_LEN) {
        return;
    }

    if (strnlen(ip, ip_size) >= ip_size) {
        return;
    }

    char result[MAX_IP_LEN] = "";
    char working_copy[MAX_IP_LEN] = "";
    size_t working_len;

    working_len = strnlen(ip, ip_size);
    if (working_len >= ip_size || working_len >= MAX_IP_LEN) {
        return;
    }
    memcpy(working_copy, ip, working_len + 1);
    working_copy[MAX_IP_LEN - 1] = '\0';

    char *token;
    char *rest = working_copy;
    int first = 1;
    size_t result_len = 0;

    while ((token = strtok_r(rest, ".", &rest)) != NULL) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }

        size_t token_len = strnlen(start, MAX_IP_LEN);
        if (token_len >= MAX_IP_LEN) {
            return;
        }

        if (!first) {
            if (result_len + 1 >= MAX_IP_LEN) {
                return;
            }
            result[result_len] = '.';
            result_len++;
        }

        if (result_len + token_len >= MAX_IP_LEN) {
            return;
        }
        memcpy(result + result_len, start, token_len);
        result_len += token_len;
        result[result_len] = '\0';

        first = 0;
    }

    size_t result_final_len = strnlen(result, MAX_IP_LEN);
    if (result_final_len >= MAX_IP_LEN) {
        return;
    }

    if (result_final_len < ip_size) {
        memcpy(ip, result, result_final_len + 1);
    } else {
        memcpy(ip, result, ip_size - 1);
        ip[ip_size - 1] = '\0';
    }
}

int main(void) {
    char ip1[MAX_IP_LEN] = "192.168.001.001";
    char ip2[MAX_IP_LEN] = "010.000.000.001";
    char ip3[MAX_IP_LEN] = "000.000.000.000";
    char ip4[MAX_IP_LEN] = "255.255.255.255";

    remove_leading_zeroes(ip1, sizeof(ip1));
    remove_leading_zeroes(ip2, sizeof(ip2));
    remove_leading_zeroes(ip3, sizeof(ip3));
    remove_leading_zeroes(ip4, sizeof(ip4));

    printf("%s\n", ip1);
    printf("%s\n", ip2);
    printf("%s\n", ip3);
    printf("%s\n", ip4);

    return 0;
}