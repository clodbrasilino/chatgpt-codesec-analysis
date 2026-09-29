#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* removeParenthesis(const char* str) {
    int len = strlen(str), i, j = 0;
    if (len == 0) {
        return NULL;
    }

    char* result = (char*)malloc(sizeof(char) * (len + 1));
    if (!result) {
        return NULL;
    }
    
    int parenthesis_level = 0;
    for (i = 0; i < len; ++i) {
        if (str[i] == '(') {
            parenthesis_level++;
        } else if (str[i] == ')') {
            if (parenthesis_level > 0) {
                parenthesis_level--;
            } else {
                free(result);
                return NULL;
            }
        } else {
            if (parenthesis_level == 0) {
                result[j++] = str[i];
            }
        }
    }
    if (parenthesis_level != 0) {
        free(result);
        return NULL;
    }

    result[j] = '\0';
    return result;
}

int main() {
    const char *str = "Hello (world)";
    char* result = removeParenthesis(str);
    
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error: Missing parenthesis\n");
    }
    return 0;
}