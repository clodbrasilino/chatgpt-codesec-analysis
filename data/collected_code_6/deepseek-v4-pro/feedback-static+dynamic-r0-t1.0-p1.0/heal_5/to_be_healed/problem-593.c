#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int remove_leading_zeroes(char *ip, size_t ip_size) {
    if (ip == NULL || ip_size == 0) {
        return 0;
    }

    if (ip_size > INET_ADDRSTRLEN) {
        ip_size = INET_ADDRSTRLEN;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[INET_ADDRSTRLEN];
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, ip, ip_size);
    temp[ip_size - 1] = '\0';

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[INET_ADDRSTRLEN];
    result[0] = '\0';
    size_t result_len = 0;

    char *saveptr;
    char *token = strtok_r(temp, ".", &saveptr);
    int first = 1;

    while (token != NULL) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t start_len = strlen(start);

        if (!first) {
            if (result_len + 1 < INET_ADDRSTRLEN) {
                result[result_len] = '.';
                result_len++;
                result[result_len] = '\0';
            } else {
                break;
            }
        }

        if (result_len + start_len < INET_ADDRSTRLEN) {
            size_t available = INET_ADDRSTRLEN - result_len - 1;
            size_t to_copy = start_len < available ? start_len : available;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, start, to_copy);
            result_len += to_copy;
            result[result_len] = '\0';
        } else {
            break;
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_len_final = strlen(result);
    if (result_len_final >= ip_size) {
        result_len_final = ip_size - 1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(ip, result, result_len_final);
    ip[result_len_final] = '\0';

    return 1;
}

int main(void) {
    char ip1[] = "192.168.001.001";
    char ip2[] = "010.000.000.001";
    char ip3[] = "000.000.000.000";
    char ip4[] = "255.255.255.255";
    char ip5[] = "001.002.003.004";

    remove_leading_zeroes(ip1, sizeof(ip1));
    remove_leading_zeroes(ip2, sizeof(ip2));
    remove_leading_zeroes(ip3, sizeof(ip3));
    remove_leading_zeroes(ip4, sizeof(ip4));
    remove_leading_zeroes(ip5, sizeof(ip5));

    printf("%s\n", ip1);
    printf("%s\n", ip2);
    printf("%s\n", ip3);
    printf("%s\n", ip4);
    printf("%s\n", ip5);

    return 0;
}