#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IP_LEN 1024

void remove_leading_zeroes(char *ip) {
    if (ip == NULL || *ip == '\0') {
        return;
    }

    size_t ip_len = strnlen(ip, MAX_IP_LEN + 1);
    if (ip_len > MAX_IP_LEN || ip_len == 0) {
        return;
    }

    char *copy = strndup(ip, ip_len);
    if (copy == NULL) {
        return;
    }

    char *saveptr;
    char *token = strtok_r(copy, ".", &saveptr);
    int first = 1;
    size_t result_len = 0;

    while (token != NULL && result_len < ip_len) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }

        size_t token_len = strnlen(start, ip_len - result_len);

        if (!first) {
            if (result_len + 1 < ip_len) {
                ip[result_len] = '.';
                result_len++;
            } else {
                break;
            }
        }

        if (token_len >= ip_len - result_len) {
            token_len = ip_len - result_len;
        }

        if (token_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(ip + result_len, start, token_len);
            result_len += token_len;
        }

        if (result_len >= ip_len) {
            break;
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    ip[result_len] = '\0';
    free(copy);
}

int main(void) {
    char ip1[] = "192.168.001.001";
    char ip2[] = "010.000.000.001";
    char ip3[] = "000.000.000.000";
    char ip4[] = "255.255.255.255";

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