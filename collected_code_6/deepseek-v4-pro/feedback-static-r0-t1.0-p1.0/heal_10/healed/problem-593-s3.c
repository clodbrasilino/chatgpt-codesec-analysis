#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int remove_leading_zeroes(char *ip, size_t ip_size) {
    if (ip == NULL || ip_size == 0) {
        return -1;
    }

    if (ip_size > 16) {
        ip_size = 16;
    }

    char result[16] = {0};
    char *copy = strdup(ip);
    
    if (copy == NULL) {
        return -1;
    }

    char *token;
    char *saveptr;
    token = strtok_r(copy, ".", &saveptr);
    int first = 1;
    size_t result_len = 0;
    
    while (token != NULL) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }
        
        if (!first) {
            if (result_len >= sizeof(result) - 1) {
                free(copy);
                return -1;
            }
            result[result_len] = '.';
            result_len++;
        }
        
        size_t token_len = 0;
        const char *p = start;
        while (*p != '\0') {
            token_len++;
            p++;
        }
        
        if (token_len >= sizeof(result) || result_len + token_len >= sizeof(result) - 1) {
            free(copy);
            return -1;
        }
        
        memcpy(result + result_len, start, token_len);
        result_len += token_len;
        result[result_len] = '\0';
        
        first = 0;
        token = strtok_r(NULL, ".", &saveptr);
    }
    
    if (result_len + 1 > ip_size) {
        free(copy);
        return -1;
    }
    
    memcpy(ip, result, result_len + 1);
    
    free(copy);
    return 0;
}

int main(void) {
    char ip1[16] = "192.168.001.001";
    char ip2[16] = "010.000.000.001";
    char ip3[16] = "000.000.000.000";
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