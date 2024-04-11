#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snakeToCamel(char* snake) {
    int i, j = 0;
    char camel[100];
    for(i = 0; i < strlen(snake); i++) {
        if(snake[i] == '_') {
            i++;
            camel[j] = toupper(snake[i]);
        } else {
            camel[j] = snake[i];
        }
        j++;
    }
    camel[j] = '\0';
    strcpy(snake, camel);
    return snake;
}

int main() {
    char snake[100];
    printf("Enter a snake case string: ");
    scanf("%s", snake);
    printf("Camel case string: %s\n", snakeToCamel(snake));
    return 0;
}