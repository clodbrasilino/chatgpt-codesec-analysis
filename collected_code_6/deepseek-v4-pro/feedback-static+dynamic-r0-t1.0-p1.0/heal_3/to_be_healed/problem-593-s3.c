#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_leading_zeroes(char *ip) {
    if (ip == NULL || *ip == '\0') {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t ip_len = strlen(ip);
    if (ip_len > 1024) {
        return;
    }

    char *result = calloc(ip_len + 1, 1);
    if (result == NULL) {
        return;
    }

    char *copy = strdup(ip);
    if (copy == NULL) {
        free(result);
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

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t token_len = strlen(start);

        if (!first) {
            if (result_len + 1 < ip_len) {
                result[result_len] = '.';
                result_len++;
            } else {
                break;
            }
        }

        if (result_len + token_len <= ip_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, start, token_len);
            result_len += token_len;
        } else {
            break;
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    if (result_len <= ip_len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ip, result, result_len);
        ip[result_len] = '\0';
    }

    free(copy);
    free(result);
}

int main(void) {
    char ip1[] = "192.168.001.001";
    char ip2[] = "010.000.000.001";
    char ip3[] = "000.000.000.000";
    char ip4[] = "255.255.255.255";

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