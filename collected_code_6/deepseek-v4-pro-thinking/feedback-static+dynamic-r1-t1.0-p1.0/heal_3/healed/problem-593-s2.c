#include <stdio.h>
#include <stddef.h>

int remove_leading_zeroes(char *ip) {
    if (ip == NULL)
        return -1;

    size_t max_len = 15;
    size_t len = 0;
    while (len < max_len && ip[len] != '\0')
        ++len;

    size_t read = 0, write = 0;
    int octet_start = 1;

    while (read < len) {
        if (ip[read] == '.') {
            if (write < max_len)
                ip[write++] = '.';
            ++read;
            octet_start = 1;
            continue;
        }

        if (octet_start) {
            while (read < len && ip[read] == '0' &&
                   read + 1 < len &&
                   ip[read + 1] >= '0' && ip[read + 1] <= '9') {
                ++read;
            }
            octet_start = 0;
        }

        if (read < len && write < max_len)
            ip[write++] = ip[read++];
    }

    if (write < max_len)
        ip[write] = '\0';
    else if (max_len > 0)
        ip[max_len - 1] = '\0';

    return 0;
}

int main(void) {
    char ip[] = "192.168.001.001";
    if (remove_leading_zeroes(ip) != 0)
        return 1;
    printf("%s\n", ip);
    return 0;
}