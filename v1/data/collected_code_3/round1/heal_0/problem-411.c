#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* snakeToCamel(char* snake) {
    int i, j = 0;
    int len = strlen(snake);
    char* camel = malloc(len * sizeof(char));

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
    char snake[] = "this_is_snake_case";
    char* camel = snakeToCamel(snake);
    printf("%s\n", camel);
    free(camel);
    return 0;
}