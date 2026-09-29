#include <stdio.h>
#include <string.h>

char* remove_leading_zeroes_ip(char *ip) {
    char *new_ip = ip;
    while (*new_ip != '\0') {
        if (*new_ip == '.') {
            new_ip++;
            continue;
        }
        char *token = new_ip;
        while (*token != '.' && *token != '\0') {
            token++;
        }
        while (token > new_ip + 1 && *new_ip == '0') {
            memmove(new_ip, new_ip + 1, token - new_ip);
        }
        if (token > new_ip + 1 && *new_ip == '0' && *(new_ip + 1) != '.') {
            /* Possible weaknesses found:
             *  Value stored to 'new_ip' is never read [deadcode.DeadStores]
             */
            new_ip = new_ip + 1;
        } else if (token - new_ip == 1) {
            break;
        }
        new_ip = token;
        if (*new_ip == '.') {
            new_ip++;
        }
    }
    return ip;
}

int main() {
    char ip[] = "010.010.001.002";
    printf("Original IP: %s\n", ip);
    char *new_ip = remove_leading_zeroes_ip(ip);
    printf("Cleaned IP: %s\n", new_ip);
    return 0;
}