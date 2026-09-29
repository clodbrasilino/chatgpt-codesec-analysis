#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip, size_t ip_len) {
    char new_ip[128] = "";
    char *new_ip_ptr = new_ip;
    char *token, *context;

    token = strtok_r(ip, ".", &context);
    while (token) {
        size_t len = strnlen(token, 16);
        if (len > 1 && *token == '0' && isdigit(*(token + 1))) {
            memmove(token, token + 1, len - 1);
            *(token + len - 2) = '\0';
        }
        len = strnlen(token, 16);
        size_t new_ip_len = strlen(new_ip);
        if (new_ip_len + len + 1 < sizeof(new_ip)) {
            memmove(new_ip_ptr, token, len);
            new_ip_ptr += len;
            *new_ip_ptr++ = '.';
        }
        token = strtok_r(NULL, ".", &context);
    }
    if (new_ip_ptr > new_ip) {
        *(new_ip_ptr - 1) = '\0';
    }

    size_t new_ip_final_len = strlen(new_ip);
    if (new_ip_final_len < ip_len - 1) {
        strncpy(ip, new_ip, ip_len - 1);
        ip[ip_len - 1] = '\0';
    } else {
        ip[0] = '\0';
    }
}

int main() {
    char ip[46] = "192.168.01.01";
    remove_leading_zeroes(ip, sizeof(ip));
    printf("%s\n", ip);
    return 0;
}