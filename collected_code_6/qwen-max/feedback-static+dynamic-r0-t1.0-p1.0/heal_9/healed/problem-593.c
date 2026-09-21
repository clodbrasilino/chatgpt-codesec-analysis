#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    char temp[16] = "";
    char *part = strtok(ip, ".");
    int index = 0;

    while (part && index < sizeof(temp) - 2) {
        size_t len = strnlen(part, 4);
        if (len > 1 && part[0] == '0') {
            int i;
            for (i = 0; i < len - 1 && part[i] == '0'; i++);
            size_t copy_len = len - i;
            if (index + copy_len <= sizeof(temp) - 2) {
                memcpy(temp + index, part + i, copy_len);
                index += copy_len;
            }
        } else {
            if (index + len <= sizeof(temp) - 2) {
                memcpy(temp + index, part, len);
                index += len;
            }
        }
        part = strtok(NULL, ".");
        if (part && index + 1 < sizeof(temp) - 2) {
            temp[index++] = '.';
        }
    }
    temp[index] = '\0';
    if (strlen(temp) < sizeof(ip)) {
        strcpy(ip, temp);
    } else {
        strncpy(ip, temp, sizeof(ip) - 1);
        ip[sizeof(ip) - 1] = '\0';
    }
}

int main() {
    char ip[] = "192.168.001.001";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}