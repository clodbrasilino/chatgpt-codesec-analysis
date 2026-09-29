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
            if (!in_octet && *src == '0') continue;
            in_octet = 1;
            *dst++ = *src;
        }
        src++;
    }
    if (in_octet && dst[-1] == '0') dst--;
    *dst = '\0';
}

int main() {
    char ip[] = "192.168.01.01";
    remove_leading_zeros(ip);
    printf("%s\n", ip);
    return 0;
}