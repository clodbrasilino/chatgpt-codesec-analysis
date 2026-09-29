#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_leading_zeroes(char *ip) {
    if (ip == NULL || *ip == '\0') {
        return;
    }

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
    
    while (token != NULL && result_len < sizeof(result) - 1) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }
        
        if (!first) {
            if (result_len < sizeof(result) - 1) {
                result[result_len] = '.';
                result_len++;
            } else {
                free(copy);
                return;
            }
        }
        
        size_t token_len = strlen(start);
        if (result_len + token_len >= sizeof(result)) {
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
    
    if (result_len >= sizeof(result)) {
        free(copy);
        return;
    }
    
    size_t ip_len = strlen(ip);
    if (ip_len < sizeof(result) && result_len <= ip_len) {
        size_t i;
        for (i = 0; i <= result_len; i++) {
            ip[i] = result[i];
        }
    }
    
    free(copy);
}

int main(void) {
    char ip1[16] = "192.168.001.001";
    char ip2[16] = "010.000.000.001";
    char ip3[16] = "000.000.000.000";
    char ip4[16] = "255.255.255.255";
    
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