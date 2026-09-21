#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isValidParentheses(const char *s) {
    if (s == NULL) return false;
    
    size_t len = strlen(s);
    
    if (len > 1048576) return false;
    
    if (len == 0) return true;
    
    char *stack = malloc(len + 1);
    if (stack == NULL) return false;
    
    int top = -1;
    
    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            stack[++top] = c;
        } else if (c == ')' || c == ']' || c == '}') {
            if (top == -1) {
                free(stack);
                return false;
            }
            char opening = stack[top--];
            if ((c == ')' && opening != '(') ||
                (c == ']' && opening != '[') ||
                (c == '}' && opening != '{')) {
                free(stack);
                return false;
            }
        }
    }
    
    bool result = (top == -1);
    free(stack);
    return result;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 0;
    
    if (getline(&input, &buffer_size, stdin) == -1) {
        free(input);
        return 1;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    if (isValidParentheses(input)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    free(input);
    return 0;
}