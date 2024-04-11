#include <stdio.h>
#include <string.h>

char* removeParenthesis(char* str) {
    int i, j = 0, count = 0;
    char* result = (char*)malloc(strlen(str) + 1);

    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] == '(') {
            count++;
        } else if(str[i] == ')') {
            count--;
        } else if(count == 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char str[] = "Hello (world)!";
    char* result = removeParenthesis(str);
    printf("%s\n", result);
    free(result);
    return 0;
}