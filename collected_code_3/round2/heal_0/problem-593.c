#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeLeadingZeroes(char* ip) {
    char *newIp = malloc(16);
    char *token;
    int index = 0;

    token = strtok(ip, ".");
    while(token != NULL) {
        int segment = atoi(token);
        index += sprintf(&newIp[index], index == 0 ? "%d" : ".%d", segment);
        token = strtok(NULL, ".");
    }

    return newIp;
}

int main() {
    char ip[16];
    printf("Enter an IP address: ");
    scanf("%s", ip);

    char *newIp = removeLeadingZeroes(ip);
    printf("IP address without leading zeroes: %s\n", newIp);

    free(newIp);
    return 0;
}