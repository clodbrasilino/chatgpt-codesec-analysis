#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

void remove_leading_zeroes(char *ip) {
    if (ip == NULL || *ip == '\0') {
        return;
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
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp, ip, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

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
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t ip_len = strlen(ip);
    if (ip_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(ip, result, ip_len);
        ip[ip_len] = '\0';
    }
}

int main(void) {
    char ip1[] = "192.168.001.001";
    char ip2[] = "010.000.000.001";
    char ip3[] = "000.000.000.000";
    char ip4[] = "255.255.255.255";
    char ip5[] = "001.002.003.004";

    remove_leading_zeroes(ip1);
    remove_leading_zeroes(ip2);
    remove_leading_zeroes(ip3);
    remove_leading_zeroes(ip4);
    remove_leading_zeroes(ip5);

    printf("%s\n", ip1);
    printf("%s\n", ip2);
    printf("%s\n", ip3);
    printf("%s\n", ip4);
    printf("%s\n", ip5);

    return 0;
}