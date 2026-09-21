#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IP_LEN 16

void remove_leading_zeroes(char *ip, size_t ip_size) {
    if (ip == NULL || ip_size == 0 || ip_size > MAX_IP_LEN) {
        return;
    }

    size_t ip_len = strnlen(ip, ip_size);
    if (ip_len >= ip_size) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[MAX_IP_LEN] = "";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char working_copy[MAX_IP_LEN] = "";
    size_t working_len;

    working_len = ip_len;
    if (working_len >= MAX_IP_LEN) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(working_copy, ip, working_len);
    working_copy[working_len] = '\0';

    char *token;
    char *rest = working_copy;
    int first = 1;
    size_t result_len = 0;

    while ((token = strtok_r(rest, ".", &rest)) != NULL) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }

        size_t token_len = strnlen(start, MAX_IP_LEN - result_len);
        if (token_len >= MAX_IP_LEN - result_len) {
            return;
        }

        if (!first) {
            if (result_len + 1 >= MAX_IP_LEN) {
                return;
            }
            result[result_len] = '.';
            result_len++;
            result[result_len] = '\0';
        }

        if (result_len + token_len >= MAX_IP_LEN) {
            return;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_len, start, token_len);
        result_len += token_len;
        result[result_len] = '\0';

        first = 0;
    }

    size_t result_final_len = strnlen(result, MAX_IP_LEN);
    if (result_final_len >= MAX_IP_LEN) {
        return;
    }

    size_t copy_len;
    if (result_final_len < ip_size) {
        copy_len = result_final_len;
    } else {
        copy_len = ip_size - 1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(ip, result, copy_len);
    ip[copy_len] = '\0';
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