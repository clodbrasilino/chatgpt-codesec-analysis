#include <stdio.h>
#include <string.h>

void remove_leading_zeros(char *ip) {
    char *src = ip, *dst = ip;
    int in_octet = 0;

    while (*src) {
        if (*src == '.') {
            if (in_octet && dst[-1] == '0') dst--;
            *dst++ = *src;
            in_octet = 0;
        } else {
            if (*src != '0' || (in_octet && dst[-1] != '0')) {
                *dst++ = *src;
                in_octet = 1;
            }
        }
        src++;
    }
    if (in_octet && dst[-1] == '0') dst--;
    *dst = '\0';
}

int main() {
    char ip[] = "192.168.001.001";
    remove_leading_zeros(ip);
    printf("%s\n", ip);
    return 0;
}