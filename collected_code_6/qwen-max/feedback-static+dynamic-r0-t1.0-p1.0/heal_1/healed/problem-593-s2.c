#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    char *token, *context, *ip_copy, *part;
    size_t len = strlen(ip);
    ip_copy = malloc(len + 1);
    if (ip_copy == NULL) return;
    strcpy(ip_copy, ip);

    token = strtok_r(ip_copy, ".", &context);
    while (token) {
        part = token;
        if (strlen(part) > 1 && *part == '0') {
            memmove(part, part + 1, strlen(part));
        }
        token = strtok_r(NULL, ".", &context);
    }

    strncpy(ip, ip_copy, len + 1);
    free(ip_copy);
}

int main() {
    char ip[16] = "192.168.01.01";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}