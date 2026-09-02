#include <stdio.h>
#include <string.h>

void remove_leading_zeros(char *ip) {
    char *src = ip, *dst = ip;
    int in_segment = 0;

    while (*src) {
        if (*src == '.') {
            *dst++ = '.';
            in_segment = 0;
        } else if (*src != '0' || in_segment) {
            *dst++ = *src;
            in_segment = 1;
        }
        src++;
    }
    *dst = '\0';
}

int main() {
    char ip[] = "192.168.01.01";
    remove_leading_zeros(ip);
    printf("%s\n", ip);
    return 0;
}