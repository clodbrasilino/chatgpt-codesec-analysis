#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int remove_leading_zeroes(char *ip, size_t ip_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'ip_size==0' is not redundant
     */
    if (ip == NULL || ip_size == 0 || *ip == '\0') {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[INET_ADDRSTRLEN] = {0};
    size_t result_len = 0;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[INET_ADDRSTRLEN] = {0};
    size_t temp_size = sizeof(temp);
    if (ip_size < temp_size) {
        temp_size = ip_size;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, ip, temp_size - 1);
    temp[temp_size - 1] = '\0';

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
            if (result_len + 1 < sizeof(result)) {
                result[result_len] = '.';
                result_len++;
                result[result_len] = '\0';
            } else {
                break;
            }
        }

        if (result_len + start_len < sizeof(result)) {
            size_t available = sizeof(result) - result_len - 1;
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
    size_t result_strlen = strlen(result);
    if (result_strlen < ip_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ip, result, result_strlen);
        ip[result_strlen] = '\0';
        return 1;
    /* Possible weaknesses found:
     *  Condition 'ip_size>0' is always true [knownConditionTrueFalse]
     *  Condition 'ip_size>0' is always true
     */
    } else if (ip_size > 0) {
        size_t to_copy = ip_size - 1;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ip, result, to_copy);
        ip[to_copy] = '\0';
        return 1;
    }

    return 0;
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