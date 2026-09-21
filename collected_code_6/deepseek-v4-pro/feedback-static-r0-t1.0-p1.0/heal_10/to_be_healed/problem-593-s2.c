#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IP_ADDR_MAX_LEN 16

void remove_leading_zeros(char *ip) {
    if (ip == NULL) return;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[IP_ADDR_MAX_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[IP_ADDR_MAX_LEN];
    char *token;
    char *saveptr;
    int first = 1;
    size_t result_len = 0;

    memset(result, 0, sizeof(result));
    memset(temp, 0, sizeof(temp));

    size_t ip_len = strnlen(ip, IP_ADDR_MAX_LEN - 1);
    size_t copy_len = ip_len < IP_ADDR_MAX_LEN ? ip_len : IP_ADDR_MAX_LEN - 1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, ip, copy_len);
    temp[copy_len] = '\0';

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

        size_t remaining = sizeof(result) - result_len - 1;
        size_t token_len = strnlen(start, remaining);
        if (token_len > remaining) {
            token_len = remaining;
        }
        if (token_len > 0 && result_len + token_len < sizeof(result)) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, start, token_len);
            result_len += token_len;
            result[result_len] = '\0';
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    result[sizeof(result) - 1] = '\0';

    size_t result_str_len = strnlen(result, sizeof(result));
    size_t final_copy_len = result_str_len < IP_ADDR_MAX_LEN ? result_str_len : IP_ADDR_MAX_LEN - 1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(ip, result, final_copy_len);
    ip[final_copy_len] = '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip1[IP_ADDR_MAX_LEN] = "192.168.001.001";
    remove_leading_zeros(ip1);
    printf("%s\n", ip1);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip2[IP_ADDR_MAX_LEN] = "010.000.000.010";
    remove_leading_zeros(ip2);
    printf("%s\n", ip2);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip3[IP_ADDR_MAX_LEN] = "0.0.0.0";
    remove_leading_zeros(ip3);
    printf("%s\n", ip3);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip4[IP_ADDR_MAX_LEN] = "255.255.255.255";
    remove_leading_zeros(ip4);
    printf("%s\n", ip4);

    return 0;
}