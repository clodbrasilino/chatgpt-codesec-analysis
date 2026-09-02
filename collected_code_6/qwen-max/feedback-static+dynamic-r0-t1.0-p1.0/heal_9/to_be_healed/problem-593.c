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
            *new_ip = '0';
            /* Possible weaknesses found:
             *  new_ip is assigned
             */
            new_ip++;
        } else if (token - new_ip == 1) {
            break;
        }
        /* Possible weaknesses found:
         *  new_ip is overwritten
         *  Variable 'new_ip' is reassigned a value before the old one has been used. [redundantAssignment]
         */
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