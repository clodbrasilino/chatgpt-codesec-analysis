#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    char *token, *context, *new_ip, *src;
    new_ip = ip;
    token = strtok_r(ip, ".", &context);
    while (token) {
        size_t len = strnlen(token, 16);
        if (len > 1 && *token == '0') {
            memmove(token, token + 1, len - 1);
            *(token + len - 1) = '\0';
        }
        len = strnlen(token, 16);
        memmove(new_ip, token, len);
        new_ip += len;
        *new_ip++ = '.';
        token = strtok_r(NULL, ".", &context);
    }
    *(new_ip - 1) = '\0'; // Remove the last added dot
}

int main() {
    char ip[16] = "192.168.01.01";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}