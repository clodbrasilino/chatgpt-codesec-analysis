#include <stdio.h>
#include <string.h>

void remove_leading_zeros(char *ip) {
    char *part = strtok(ip, ".");
    while (part) {
        if (strlen(part) > 1 && part[0] == '0') {
            char *src = part + 1;
            memmove(part, src, strlen(src) + 1);
        }
        part = strtok(NULL, ".");
    }
}

int main() {
    char ip_address[] = "0192.0168.01.01";
    remove_leading_zeros(ip_address);
    printf("%s\n", ip_address);
    return 0;
}