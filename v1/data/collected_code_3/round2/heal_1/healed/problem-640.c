#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeParenthesis(char* str) {
    int i, j = 0, count = 0;
    char* result = (char*)malloc(strlen(str) + 1);

    if (result == NULL) {
        return NULL;
    }

    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] == '(') {
            count++;
            continue;
        } else if(str[i] == ')') {
            count--;
            continue;
        }

        if(count == 0) {
            result[j] = str[i];
            j++;
        }
    }
    
    result[j] = '\0';
    return result;
}

int main() {
    char str[] = "Hello (world)!";
    char* result = removeParenthesis(str);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}