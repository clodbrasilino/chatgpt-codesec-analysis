#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeParenthesis(char* str) {
    int i = 0, j = 0;
    int inParenthesis = 0;

    char *result = (char*)malloc(strlen(str) + 1);
    if(result == NULL) {
        return NULL;
    }
  
    while(str[i]) {
        if(str[i] == '(') {
            inParenthesis = 1;
        } else if(str[i] == ')') {
            inParenthesis = 0;
            i++;
            continue;
        }
        if(!inParenthesis) {
            result[j++] = str[i];
        }
        i++;
    }
    result[j] = '\0';
    return result;
}

int main() {
    char str[] = "Hello (world)!";
  
    char *result = removeParenthesis(str);
    if(result == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    printf("%s\n", result);
  
    free(result);
    return 0;
}