#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int remove_leading_zeroes(char *ip, size_t ip_size) {
    if (ip == NULL || ip_size == 0 || ip_size > INET_ADDRSTRLEN) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[INET_ADDRSTRLEN];
    size_t copy_size = ip_size < INET_ADDRSTRLEN ? ip_size : INET_ADDRSTRLEN;
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp, ip, copy_size);
    temp[copy_size - 1] = '\0';

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

        size_t start_len = strnlen(start, INET_ADDRSTRLEN);

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
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result + result_len, start, to_copy);
            result_len += to_copy;
            result[result_len] = '\0';
        } else {
            break;
        }

        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }

    size_t result_len_final = strnlen(result, INET_ADDRSTRLEN);
    if (result_len_final >= ip_size) {
        result_len_final = ip_size - 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(ip, result, result_len_final);
    ip[result_len_final] = '\0';

    return 1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip1[INET_ADDRSTRLEN] = "192.168.001.001";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip2[INET_ADDRSTRLEN] = "010.000.000.001";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip3[INET_ADDRSTRLEN] = "000.000.000.000";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip4[INET_ADDRSTRLEN] = "255.255.255.255";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip5[INET_ADDRSTRLEN] = "001.002.003.004";

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