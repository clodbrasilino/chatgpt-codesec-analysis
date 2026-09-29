#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_leading_zeroes(char *ip, size_t ip_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'ip_size==0' is not redundant
     */
    if (ip == NULL || ip_size == 0) return;
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[16] = "";
    char *token;
    char *rest = ip;
    int first = 1;
    size_t result_len = 0;
    
    while ((token = strtok_r(rest, ".", &rest)) != NULL) {
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
        size_t token_len = strlen(start);
        if (result_len + token_len < sizeof(result)) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, start, token_len);
            result_len += token_len;
            result[result_len] = '\0';
        }
        first = 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_final_len = strlen(result);
    if (result_final_len < ip_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ip, result, result_final_len + 1);
    /* Possible weaknesses found:
     *  Condition 'ip_size>0' is always true
     *  Condition 'ip_size>0' is always true [knownConditionTrueFalse]
     */
    } else if (ip_size > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ip, result, ip_size - 1);
        ip[ip_size - 1] = '\0';
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip1[16] = "192.168.001.001";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip2[16] = "010.000.000.001";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip3[16] = "000.000.000.000";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip4[16] = "255.255.255.255";
    
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