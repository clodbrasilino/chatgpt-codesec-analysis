#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRLEN 100

void abbreviateRoad(char* str, int len) {
    if (str == NULL || len < 4)
        return;

    char temp[MAX_STRLEN+1] = {'\0'}; 
    strncpy(temp, str, len);
    temp[len] = '\0';

    char *start = strstr(temp, "road");
    if (start) {
        *start++ = 'r';
        *start++ = 'd';
        *start = '\0';
    }

    strncpy(str, temp, len);
    str[len] = '\0';
}

int main() {
    char* str = (char*) malloc(sizeof(char) * (MAX_STRLEN + 1));

    if (str == NULL){
        printf("Memory allocation failed!\n");
        return -1;
    }

    printf("Enter a string: ");
    fgets(str, MAX_STRLEN, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    int len = strnlen(str, MAX_STRLEN);
    abbreviateRoad(str, len);

    printf("Abbreviated string: %s\n", str);
    free(str);
    return 0;
}