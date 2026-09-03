#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void remove_leading_zeroes(char *ip) {
    if (ip == NULL) return;
    
    char *src = ip;
    char *dst = ip;
    int segment_start = 1;
    
    while (*src) {
        if (*src == '.') {
            *dst++ = *src++;
            segment_start = 1;
            continue;
        }
        
        if (segment_start) {
            while (*src == '0' && isdigit(*(src + 1)) && *(src + 1) != '.') {
                src++;
            }
            segment_start = 0;
        }
        
        *dst++ = *src++;
    }
    
    *dst = '\0';
}

int main(void) {
    char ip1[] = "192.168.001.001";
    char ip2[] = "010.000.000.001";
    char ip3[] = "001.002.003.004";
    char ip4[] = "000.000.000.000";
    char ip5[] = "255.255.255.255";
    char ip6[] = "001.010.100.001";
    
    remove_leading_zeroes(ip1);
    remove_leading_zeroes(ip2);
    remove_leading_zeroes(ip3);
    remove_leading_zeroes(ip4);
    remove_leading_zeroes(ip5);
    remove_leading_zeroes(ip6);
    
    printf("%s\n", ip1);
    printf("%s\n", ip2);
    printf("%s\n", ip3);
    printf("%s\n", ip4);
    printf("%s\n", ip5);
    printf("%s\n", ip6);
    
    return 0;
}