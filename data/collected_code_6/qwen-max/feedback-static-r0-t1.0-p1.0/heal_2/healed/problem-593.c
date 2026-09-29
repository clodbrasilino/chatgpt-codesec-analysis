#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    char temp[16] = "";
    char *part = strtok(ip, ".");
    int index = 0;

    while (part != NULL) {
        if (strlen(part) > 1 && part[0] == '0') {
            size_t len;
            for (len = 0; part[len] == '0' && len < strlen(part) - 1; len++);
            len = strlen(part + len);
            if (index + len < sizeof(temp) - 2) {
                strncpy(temp + index, part + len, len);
                temp[index + len] = '\0';
                index += len;
            }
        } else {
            size_t len = strlen(part);
            if (index + len < sizeof(temp) - 2) {
                strncpy(temp + index, part, len);
                temp[index + len] = '\0';
                index += len;
            }
        }
        if (part = strtok(NULL, ".")) {
            if (index < sizeof(temp) - 2) {
                temp[index++] = '.';
                temp[index] = '\0';
            }
        }
    }
    if (strlen(temp) < strlen(ip)) {
        snprintf(ip, sizeof(ip), "%s", temp);
    }
}

int main() {
    char ip[] = "192.168.001.001";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}