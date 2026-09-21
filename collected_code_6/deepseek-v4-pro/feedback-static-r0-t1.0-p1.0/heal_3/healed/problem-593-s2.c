#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void remove_leading_zeros(char *ip) {
    if (ip == NULL) return;

    char result[16];
    char temp[16];
    char *token;
    char *saveptr;
    int first = 1;
    size_t result_len = 0;

    memset(result, 0, sizeof(result));
    memset(temp, 0, sizeof(temp));

    size_t ip_len = strlen(ip);
    if (ip_len >= sizeof(temp)) {
        ip_len = sizeof(temp) - 1;
    }
    memcpy(temp, ip, ip_len);
    temp[ip_len] = '\0';

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

        size_t token_len = strlen(start);
        size_t remaining = sizeof(result) - result_len - 1;
        if (token_len > remaining) {
            token_len = remaining;
        }
        if (token_len > 0) {
            memcpy(result + result_len, start, token_len);
            result_len += token_len;
            result[result_len] = '\0';
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    result[sizeof(result) - 1] = '\0';
    
    size_t result_copy_len = strlen(result);
    if (result_copy_len > 15) {
        result_copy_len = 15;
    }
    memcpy(ip, result, result_copy_len);
    ip[result_copy_len] = '\0';
}

int main(void) {
    char ip1[] = "192.168.001.001";
    remove_leading_zeros(ip1);
    printf("%s\n", ip1);

    char ip2[] = "010.000.000.010";
    remove_leading_zeros(ip2);
    printf("%s\n", ip2);

    char ip3[] = "0.0.0.0";
    remove_leading_zeros(ip3);
    printf("%s\n", ip3);

    char ip4[] = "255.255.255.255";
    remove_leading_zeros(ip4);
    printf("%s\n", ip4);

    return 0;
}