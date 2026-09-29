#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* snakeToCamel(char* snake_str) {
    int i, j = 0;
    int len = strlen(snake_str);
    
    char* camel_str = (char*) malloc(sizeof(char) * (len + 1));

    if(camel_str == NULL) {
        return NULL;
    }

    for(i = 0; i < len; i++) {
        if(snake_str[i] == '_') {
            i++;
            camel_str[j] = toupper(snake_str[i]);
        } else {
            camel_str[j] = snake_str[i];
        }
        j++;
    }
    camel_str[j] = '\0';
    return camel_str;
}

int main() {
    char snake_str[100];
    printf("Enter a snake case string: ");
    scanf("%99s", snake_str);
    char* camel_str = snakeToCamel(snake_str);
    if(camel_str == NULL)
    {
        printf("Memory allocation failed. Exiting\n");
        return 1;
    }
    printf("Camel case string: %s\n", camel_str);
    free(camel_str);
    return 0;
}