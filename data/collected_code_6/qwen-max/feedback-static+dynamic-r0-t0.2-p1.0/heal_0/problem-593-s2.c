#include <stdio.h>
#include <string.h>

void remove_leading_zeros(char *ip) {
    char *src = ip, *dst = ip;
    int in_octet = 1;

    while (*src) {
        if (*src == '0' && in_octet && (src == ip || *(src - 1) == '.')) {
            src++;
            continue;
        }
        if (*src == '.') {
            in_octet = 1;
        } else {
            in_octet = 0;
        }
        *dst++ = *src++;
    }
    *dst = '\0';
}

int main() {
    char ip[] = "192.168.001.001";
    remove_leading_zeros(ip);
    printf("%s\n", ip);
    return 0;
}