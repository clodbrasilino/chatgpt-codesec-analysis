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

        if (token_len > ip_len - result_len) {
            token_len = ip_len - result_len;
        }

        if (token_len > 0) {
            if (result_len + token_len <= ip_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(ip + result_len, start, token_len);
                result_len += token_len;
            } else {
                break;
            }
        }

        if (result_len >= ip_len) {
            break;
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    if (result_len <= ip_len) {
        ip[result_len] = '\0';
    } else {
        ip[ip_len] = '\0';
    }
    free(copy);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip1[MAX_IP_LEN] = "192.168.001.001";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip2[MAX_IP_LEN] = "010.000.000.001";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip3[MAX_IP_LEN] = "000.000.000.000";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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