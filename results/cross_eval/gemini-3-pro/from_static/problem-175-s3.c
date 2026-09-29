#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValidParentheses(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t capacity = 64;
    char *stack = (char *)malloc(capacity * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    int top = -1;
    for (size_t i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        
        if (c == '(' || c == '{' || c == '[') {
            if ((size_t)(top + 1) >= capacity) {
                capacity *= 2;
                char *new_stack = (char *)realloc(stack, capacity * sizeof(char));
                if (new_stack == NULL) {
                    free(stack);
                    return false;
                }
                stack = new_stack;
            }
            stack[++top] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == -1) {
                free(stack);
                return false;
            }
            char topChar = stack[top--];
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '[')) {
                free(stack);
                return false;
            }
        }
    }

    bool isValid = (top == -1);
    free(stack);
    return isValid;
}

int main(void) {
    const char *test1 = "()";
    const char *test2 = "()[]{}";
    const char *test3 = "(]";
    const char *test4 = "([)]";
    const char *test5 = "{[]}";

    printf("%s: %s\n", test1, isValidParentheses(test1) ? "valid" : "invalid");
    printf("%s: %s\n", test2, isValidParentheses(test2) ? "valid" : "invalid");
    printf("%s: %s\n", test3, isValidParentheses(test3) ? "valid" : "invalid");
    printf("%s: %s\n", test4, isValidParentheses(test4) ? "valid" : "invalid");
    printf("%s: %s\n", test5, isValidParentheses(test5) ? "valid" : "invalid");

    return 0;
}