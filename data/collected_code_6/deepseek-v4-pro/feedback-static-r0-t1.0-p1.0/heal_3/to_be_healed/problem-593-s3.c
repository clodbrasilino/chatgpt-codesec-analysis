#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_leading_zeroes(char *ip) {
    if (ip == NULL || *ip == '\0') {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[16] = {0};
    char *token;
    char *saveptr;
    char *copy = strdup(ip);
    
    if (copy == NULL) {
        return;
    }

    token = strtok_r(copy, ".", &saveptr);
    int first = 1;
    size_t result_len = 0;
    
    while (token != NULL && result_len < sizeof(result)) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }
        
        if (!first) {
            if (result_len < sizeof(result) - 1) {
                result[result_len] = '.';
                result_len++;
            }
        }
        
        size_t token_len = 0;
        /* Possible weaknesses found:
         *  Array index 'token_len' is used before limits check. [arrayIndexThenCheck]
         */
        while (start[token_len] != '\0' && token_len < sizeof(result) - result_len - 1) {
            token_len++;
        }
        
        if (start[token_len] != '\0') {
            free(copy);
            return;
        }

        size_t i;
        for (i = 0; i < token_len; i++) {
            result[result_len + i] = start[i];
        }
        result_len += token_len;
        result[result_len] = '\0';
        
        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }
    
    size_t result_len_final = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Array index 'result_len_final' is used before limits check. [arrayIndexThenCheck]
     *  Either the condition 'result_len_final>=16' is redundant or the array 'result[16]' is accessed at index 16, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (result[result_len_final] != '\0' && result_len_final < sizeof(result)) {
        result_len_final++;
    }
    
    size_t ip_len = 0;
    /* Possible weaknesses found:
     *  Array index 'ip_len' is used before limits check. [arrayIndexThenCheck]
     */
    while (ip[ip_len] != '\0' && ip_len < 16) {
        ip_len++;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'result_len_final>=16' is not redundant
     */
    if (ip_len >= 16 || result_len_final >= 16) {
        free(copy);
        return;
    }
    
    if (result_len_final <= ip_len) {
        size_t i;
        for (i = 0; i <= result_len_final && i < 16; i++) {
            ip[i] = result[i];
        }
    } else {
        free(copy);
        return;
    }
    
    free(copy);
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