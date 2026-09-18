#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *removeLeadingZeroes(char *ip) {
    char buf[4];
    char *newIP = malloc(sizeof(char) * strlen(ip));
    if(newIP == NULL)
        return NULL;
    
    newIP[0] = '\0';

    char *token = strtok(ip, ".");
    while(token != NULL) {
        sprintf(buf, "%d.", atoi(token));
        strcat(newIP, buf);
        token = strtok(NULL, ".");
    }
    newIP[strlen(newIP) - 1] = '\0'; 
   
    return newIP;
}

int main() {
    char ip[15];
    printf("Enter an IP address: ");
    scanf("%s", ip);

    char *newIP = removeLeadingZeroes(ip);
    if(newIP != NULL) {
        printf("IP address after removing leading zeros: %s\n", newIP);
        free(newIP);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}