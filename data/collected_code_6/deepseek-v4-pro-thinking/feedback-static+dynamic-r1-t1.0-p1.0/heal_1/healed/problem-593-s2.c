#include <stdio.h>
#include <string.h>

int remove_leading_zeroes(char *ip) {
    if (ip == NULL) return -1;
    size_t len = strlen(ip);
    size_t write = 0, read = 0;
    int at_octet_start = 1;

    while (read < len) {
        if (ip[read] == '.') {
            ip[write++] = '.';
            read++;
            at_octet_start = 1;
            continue;
        }
        if (at_octet_start) {
            while (read < len && ip[read] == '0' && read + 1 < len &&
                   ip[read + 1] >= '0' && ip[read + 1] <= '9') {
                read++;
            }
            at_octet_start = 0;
        }
        if (read < len) {
            ip[write++] = ip[read++];
        }
    }
    ip[write] = '\0';
    return 0;
}

int main(void) {
    char ip[] = "192.168.001.001";
    if (remove_leading_zeroes(ip) != 0) return 1;
    printf("%s\n", ip);
    return 0;
}