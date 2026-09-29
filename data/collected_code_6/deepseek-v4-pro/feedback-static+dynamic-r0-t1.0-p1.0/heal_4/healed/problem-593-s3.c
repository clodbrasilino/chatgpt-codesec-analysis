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

    char *result = calloc(ip_len + 1, 1);
    if (result == NULL) {
        return;
    }

    char *copy = strndup(ip, ip_len);
    if (copy == NULL) {
        free(result);
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
                result[result_len] = '.';
                result_len++;
            } else {
                break;
            }
        }

        if (token_len < ip_len - result_len) {
            memcpy(result + result_len, start, token_len);
            result_len += token_len;
        } else {
            size_t copy_len = ip_len - result_len;
            if (copy_len > 0) {
                memcpy(result + result_len, start, copy_len);
                result_len += copy_len;
            }
            break;
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    result[result_len] = '\0';

    size_t copy_len = result_len < ip_len ? result_len : ip_len;
    memcpy(ip, result, copy_len);
    ip[copy_len] = '\0';

    free(copy);
    free(result);
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