#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* snakeToCamel(char* snake) {
    int i, j = 0;
    int len = strlen(snake);
    char* camel = malloc(len+1);

    if(camel == NULL) {
        return NULL;
    }

    for(i = 0; i < len; i++) {
        if(snake[i] == '_') {
            i++;
            camel[j] = toupper(snake[i]);
        } else {
            camel[j] = snake[i];
        }
        j++;
    }
    camel[j] = '\0';
    return camel;
}

int main() {
    char snake[] = "this_is_a_snake_case_string";
    char* camel = snakeToCamel(snake);

    if(camel == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", camel);
    free(camel);
    return 0;
}