#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeLeadingZeroes(char* ip) {
    char *new_ip = malloc(16);
    if (new_ip == NULL) {
        return NULL;
    }

    int i = 0, j = 0, zero_flag = 0;

    while(ip[i]) {
        if(ip[i] == '0' && ip[i+1] != '.' && ip[i+1] != '\0' && zero_flag == 0) {
            i++;
            continue;
        }
        if(ip[i] == '.') {
            zero_flag = 0;
        } else {
            zero_flag = 1;
        }

        new_ip[j++] = ip[i++];
    }

    new_ip[j] = '\0';
    return new_ip;
}

int main() {
    char ip[16];
    printf("Enter an IP address: ");
    scanf("%15s", ip);
    char *new_ip = removeLeadingZeroes(ip);
    if(new_ip == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("IP address after removing leading zeroes: %s\n", new_ip);
    free(new_ip);
    return 0;
}