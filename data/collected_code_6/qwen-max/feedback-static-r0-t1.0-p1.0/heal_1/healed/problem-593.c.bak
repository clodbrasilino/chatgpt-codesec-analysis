#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    char temp[16];
    char *part = strtok(ip, ".");
    int index = 0;

    while (part != NULL) {
        if (strlen(part) > 1 && part[0] == '0') {
            int i;
            for (i = 0; i < strlen(part) - 1 && part[i] == '0'; i++);
            strcpy(temp + index, part + i);
        } else {
            strcpy(temp + index, part);
        }
        index += strlen(temp + index);
        if ((part = strtok(NULL, ".")) != NULL) {
            temp[index++] = '.';
        }
    }
    temp[index] = '\0';
    strcpy(ip, temp);
}

int main() {
    char ip[] = "192.168.001.001";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}