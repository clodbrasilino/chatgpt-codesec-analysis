#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IP_BUFFER_SIZE 16

void remove_leading_zeroes(char *ip) {
    if (ip == NULL) return;
    
    char result[IP_BUFFER_SIZE] = "";
    char *token;
    char *rest = ip;
    int first = 1;
    size_t current_length = 0;
    char ip_copy[IP_BUFFER_SIZE];
    
    strncpy(ip_copy, ip, IP_BUFFER_SIZE - 1);
    ip_copy[IP_BUFFER_SIZE - 1] = '\0';
    
    while ((token = strtok_r(rest, ".", &rest)) != NULL) {
        char *start = token;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }
        
        if (!first) {
            if (current_length < IP_BUFFER_SIZE - 1) {
                result[current_length] = '.';
                current_length++;
                result[current_length] = '\0';
            }
        }
        
        size_t token_length = strlen(start);
        if (current_length + token_length < IP_BUFFER_SIZE) {
            strncpy(result + current_length, start, IP_BUFFER_SIZE - current_length - 1);
            result[IP_BUFFER_SIZE - 1] = '\0';
            current_length += token_length;
        }
        
        first = 0;
    }
    
    size_t result_len = strlen(result);
    if (result_len < IP_BUFFER_SIZE) {
        strncpy(ip, result, IP_BUFFER_SIZE - 1);
        ip[IP_BUFFER_SIZE - 1] = '\0';
    }
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