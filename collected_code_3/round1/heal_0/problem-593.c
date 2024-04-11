#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeLeadingZeroes(char* ip) {
    char* result = malloc(16);
    char* token = strtok(ip, ".");
    int index = 0;

    while(token != NULL) {
        int num = atoi(token);
        if(index != 0) {
            result[index++] = '.';
        }
        sprintf(result + index, "%d", num);
        index = strlen(result);
        token = strtok(NULL, ".");
    }

    return result;
}

int main() {
    char ip[16] = "192.168.001.001";
    char* result = removeLeadingZeroes(ip);
    printf("%s\n", result);
    free(result);
    return 0;
}