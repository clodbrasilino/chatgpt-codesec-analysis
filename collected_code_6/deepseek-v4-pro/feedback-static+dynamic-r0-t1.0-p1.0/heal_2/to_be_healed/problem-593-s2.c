#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int remove_leading_zeros(char *ip, size_t ip_size) {
    if (ip == NULL || ip_size == 0) return -1;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[16] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[16] = {0};
    char *token;
    char *saveptr;
    int first = 1;
    size_t result_len = 0;

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp, ip, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

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
            }
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t seg_len = strlen(start);
        if (result_len + seg_len < sizeof(result)) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result + result_len, start, sizeof(result) - result_len - 1);
            result_len += seg_len;
        }
        first = 0;

        token = strtok_r(NULL, ".", &saveptr);
    }

    result[sizeof(result) - 1] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t copy_len = strlen(result);
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
    char ip1[16] = "192.168.001.001";
    remove_leading_zeros(ip1, sizeof(ip1));
    printf("%s\n", ip1);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip2[16] = "010.000.000.010";
    remove_leading_zeros(ip2, sizeof(ip2));
    printf("%s\n", ip2);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip3[16] = "0.0.0.0";
    remove_leading_zeros(ip3, sizeof(ip3));
    printf("%s\n", ip3);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip4[16] = "255.255.255.255";
    remove_leading_zeros(ip4, sizeof(ip4));
    printf("%s\n", ip4);

    return 0;
}