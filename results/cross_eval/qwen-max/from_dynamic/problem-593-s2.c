#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    char *token, *context;
    token = strtok_r(ip, ".", &context);
    while (token) {
        if (strlen(token) > 1 && *token == '0') {
            memmove(token, token + 1, strlen(token));
        }
        token = strtok_r(NULL, ".", &context);
    }
}

int main() {
    char ip[16] = "192.168.01.01";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}