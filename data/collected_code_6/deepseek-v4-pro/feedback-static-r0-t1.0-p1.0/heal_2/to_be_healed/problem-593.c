#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INET_ADDRSTRLEN 16

void remove_leading_zeroes(char *ip) {
    if (ip == NULL || *ip == '\0') {
        return;
    }

    char *token;
    char *saveptr;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[INET_ADDRSTRLEN];
    size_t offset = 0;
    int first = 1;

    token = strtok_r(ip, ".", &saveptr);

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (token != NULL) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }

        if (!first) {
            if (offset < sizeof(result) - 1) {
                result[offset++] = '.';
                result[offset] = '\0';
            }
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(start);
        if (offset + len < sizeof(result)) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, start, len);
            offset += len;
            result[offset] = '\0';
        } else {
            break;
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    /* Possible weaknesses found:
     *  Uninitialized variable: result
     *  Uninitialized variable: result [uninitvar]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(result) < strlen(ip) + 1) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memcpy(ip, result, strlen(result) + 1);
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