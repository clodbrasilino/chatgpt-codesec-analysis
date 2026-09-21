#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int remove_leading_zeros(char *ip, size_t ip_size) {
    if (ip == NULL || ip_size == 0 || ip_size > 64) return -1;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[64];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[64];
    char *token;
    char *saveptr;
    int first = 1;
    size_t result_len = 0;

    memset(result, 0, sizeof(result));
    memset(temp, 0, sizeof(temp));

    size_t ip_len = strnlen(ip, ip_size);
    if (ip_len >= sizeof(temp)) {
        return -1;
    }

    if (strlcpy(temp, ip, sizeof(temp)) >= sizeof(temp)) {
        return -1;
    }

    token = strtok_r(temp, ".", &saveptr);
    while (token != NULL) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }

        if (!first) {
            if (result_len < sizeof(result) - 1) {
                result[result_len] = '.';
                result_len++;
                result[result_len] = '\0';
            } else {
                return -1;
            }
        }

        size_t seg_len = strnlen(start, sizeof(result) - result_len - 1);
        if (seg_len >= sizeof(result) - result_len) {
            return -1;
        }

        if (seg_len > 0) {
            if (result_len + seg_len < sizeof(result)) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, start, seg_len);
                result_len += seg_len;
                result[result_len] = '\0';
            } else {
                return -1;
            }
        } else {
            if (result_len < sizeof(result) - 1) {
                result[result_len] = '0';
                result_len++;
                result[result_len] = '\0';
            } else {
                return -1;
            }
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    size_t copy_len = strnlen(result, sizeof(result));
    if (copy_len >= ip_size) {
        copy_len = ip_size - 1;
    }
    memmove(ip, result, copy_len);
    ip[copy_len] = '\0';

    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip1[64] = "192.168.001.001";
    remove_leading_zeros(ip1, sizeof(ip1));
    printf("%s\n", ip1);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip2[64] = "010.000.000.010";
    remove_leading_zeros(ip2, sizeof(ip2));
    printf("%s\n", ip2);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip3[64] = "0.0.0.0";
    remove_leading_zeros(ip3, sizeof(ip3));
    printf("%s\n", ip3);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip4[64] = "255.255.255.255";
    remove_leading_zeros(ip4, sizeof(ip4));
    printf("%s\n", ip4);

    return 0;
}