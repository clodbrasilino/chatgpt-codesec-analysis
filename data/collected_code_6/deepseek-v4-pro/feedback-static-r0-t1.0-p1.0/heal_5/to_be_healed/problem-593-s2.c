#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void remove_leading_zeros(char *ip) {
    if (ip == NULL) return;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[16];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[16];
    char *token;
    char *saveptr;
    int first = 1;
    size_t result_len = 0;

    memset(result, 0, sizeof(result));
    memset(temp, 0, sizeof(temp));

    size_t ip_len = strnlen(ip, sizeof(temp) - 1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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

        size_t token_len = strnlen(start, sizeof(result) - result_len - 1);
        size_t remaining = sizeof(result) - result_len - 1;
        if (token_len > remaining) {
            token_len = remaining;
        }
        if (token_len > 0) {
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
    
    size_t result_copy_len = strnlen(result, 15);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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