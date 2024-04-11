#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snakeToCamel(char* snakeStr) {
    int i, j = 0;
    int len = strlen(snakeStr);
    char* camelStr = (char*)malloc(sizeof(char) * (len + 1));

    if(camelStr == NULL) {
        return NULL;
    }

    for(i = 0; i < len; i++) {
        if(snakeStr[i] == '_') {
            i++;
            camelStr[j] = toupper(snakeStr[i]);
        } else {
            camelStr[j] = snakeStr[i];
        }
        j++;
    }
    camelStr[j] = '\0';
    return camelStr;
}

int main() {
    char snakeStr[100];
    printf("Enter a snake case string: ");
    scanf("%s", snakeStr);
    char* camelStr = snakeToCamel(snakeStr);
    if(camelStr == NULL) {
        return 1; 
    }
    printf("Camel case string: %s\n", camelStr);
    free(camelStr);
    return 0; 
}