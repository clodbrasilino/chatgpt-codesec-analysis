#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* abbreviateRoad(char* str) {
    char* result = (char*)malloc(strlen(str) + 1);
    char* token = strtok(str, " ");
    if(result != NULL){
        *result = '\0';
        while (token != NULL) {
            if (strcmp(token, "road") == 0) {
                strcat(result, "rd. ");
            } else {
                strcat(result, token);
                strcat(result, " ");
            }
            token = strtok(NULL, " ");
        }
    }        
    return result;
}

int main() {
    char str[] = "I live on a long road";
    char* result = abbreviateRoad(str);
    if(result != NULL){
        printf("%s\n", result);
        free(result);
    }
    return 0;
}