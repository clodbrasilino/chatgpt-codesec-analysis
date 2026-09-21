#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    char *token, *context;
    char new_ip[128];
    char *new_ip_ptr = new_ip;
    token = strtok_r(ip, ".", &context);
    while (token) {
        size_t len = strnlen(token, 16);
        if (len > 1 && *token == '0') {
            memmove(token, token + 1, len - 1);
            *(token + len - 1) = '\0';
        }
        len = strnlen(token, 16);
        memmove(new_ip_ptr, token, len);
        new_ip_ptr += len;
        *new_ip_ptr++ = '.';
        token = strtok_r(NULL, ".", &context);
    }
    *(new_ip_ptr - 1) = '\0';
    strcpy(ip, new_ip);
}

int main() {
    char ip[46] = "192.168.01.01";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}