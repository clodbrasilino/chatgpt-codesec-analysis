#include <stdio.h>

void remove_leading_zeroes(char *ip) {
    if (ip == NULL) {
        return;
    }
    
    int r = 0;
    int w = 0;
    
    while (ip[r] != '\0') {
        while (ip[r] == '0' && ip[r + 1] != '.' && ip[r + 1] != '\0') {
            r++;
        }
        while (ip[r] != '.' && ip[r] != '\0') {
            ip[w++] = ip[r++];
        }
        if (ip[r] == '.') {
            ip[w++] = ip[r++];
        }
    }
    
    ip[w] = '\0';
}

int main(void) {
    char ip1[] = "192.168.001.010";
    char ip2[] = "010.000.000.000";
    char ip3[] = "0.0.0.0";
    char ip4[] = "255.255.255.255";
    char ip5[] = "000";
    
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