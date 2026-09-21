#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    char temp[16] = "";
    char *part;
    int index = 0;

    part = strtok(ip, ".");
    while (part && index < sizeof(temp) - 2) {
        if (strlen(part) > 1 && part[0] == '0' && part[1] != '\0') {
            size_t len = strlen(part);
            for (size_t i = 0; i < len; i++) {
                if (part[i] == '0' && i + 1 < len) {
                    continue;
                }
                size_t new_len = len - i;
                if (index + new_len < sizeof(temp) - 2) {
                    memcpy(temp + index, part + i, new_len);
                    temp[index + new_len] = '\0';
                    index += new_len;
                    break;
                } else {
                    break;
                }
            }
        } else {
            size_t len = strlen(part);
            if (index + len < sizeof(temp) - 2) {
                memcpy(temp + index, part, len);
                temp[index + len] = '\0';
                index += len;
            } else {
                break;
            }
        }
        part = strtok(NULL, ".");
        if (part && index < sizeof(temp) - 2) {
            temp[index++] = '.';
            temp[index] = '\0';
        }
    }
    if (strlen(temp) < strlen(ip)) {
        snprintf(ip, sizeof(temp), "%s", temp);
    } else {
        strncpy(ip, temp, sizeof(temp) - 1);
        ip[sizeof(temp) - 1] = '\0';
    }
}

int main() {
    char ip[] = "192.168.001.001";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}