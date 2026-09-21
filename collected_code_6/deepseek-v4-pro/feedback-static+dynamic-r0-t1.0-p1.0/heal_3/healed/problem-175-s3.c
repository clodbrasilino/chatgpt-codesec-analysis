#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isValidParentheses(const char *s) {
    if (s == NULL) return false;
    
    size_t len = strlen(s);
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
    
    printf("Enter a string of parentheses: ");
    ssize_t read_len = getline(&input, &buffer_size, stdin);
    if (read_len == -1) {
        free(input);
        return 1;
    }
    
    if (read_len > 0 && input[read_len - 1] == '\n') {
        input[read_len - 1] = '\0';
        read_len--;
    }
    
    if (read_len == 0) {
        free(input);
        return 0;
    }
    
    if (isValidParentheses(input)) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }
    
    free(input);
    return 0;
}