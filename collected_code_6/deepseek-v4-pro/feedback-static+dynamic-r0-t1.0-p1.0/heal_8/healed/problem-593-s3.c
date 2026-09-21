#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IP_LEN 1024

void remove_leading_zeroes(char *ip) {
    if (ip == NULL || *ip == '\0') {
        return;
    }

    size_t ip_len = strnlen(ip, MAX_IP_LEN);
    if (ip_len >= MAX_IP_LEN || ip_len == 0) {
        return;
    }

    char *copy = strndup(ip, ip_len);
    if (copy == NULL) {
        return;
    }

    char *result = calloc(MAX_IP_LEN, sizeof(char));
    if (result == NULL) {
        free(copy);
        return;
    }

    size_t result_len = 0;
    char *saveptr;
    char *token = strtok_r(copy, ".", &saveptr);
    int first = 1;

    while (token != NULL) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }

        size_t token_len = strnlen(start, MAX_IP_LEN - result_len - 1);

        if (!first) {
            if (result_len < MAX_IP_LEN - 1) {
                result[result_len] = '.';
                result_len++;
            } else {
                break;
            }
        }

        if (token_len > MAX_IP_LEN - result_len - 1) {
            token_len = MAX_IP_LEN - result_len - 1;
        }

        if (token_len > 0) {
            memcpy(result + result_len, start, token_len);
            result_len += token_len;
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    result[result_len] = '\0';

    size_t copy_len = strnlen(result, MAX_IP_LEN - 1);
    if (copy_len < MAX_IP_LEN) {
        memcpy(ip, result, copy_len + 1);
    }

    free(result);
    free(copy);
}

int main(void) {
    char ip1[MAX_IP_LEN] = "192.168.001.001";
    char ip2[MAX_IP_LEN] = "010.000.000.001";
    char ip3[MAX_IP_LEN] = "000.000.000.000";
    char ip4[MAX_IP_LEN] = "255.255.255.255";

    remove_leading_zeroes(ip1);
    remove_leading_zeroes(ip2);
    remove_leading_zeroes(ip3);
    remove_leading_zeroes(ip4);

    printf("%s\n", ip1);
    printf("%s\n", ip2);
    printf("%s\n", ip3);
    printf("%s\n", ip4);

    return 0;
}