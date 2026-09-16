#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool is_valid_parentheses(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len == SIZE_MAX) {
        return false;
    }

    char *stack = malloc(len + 1);
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;

    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                free(stack);
                return false;
            }
            char open = stack[--top];
            if ((c == ')' && open != '(') ||
                (c == '}' && open != '{') ||
                (c == ']' && open != '[')) {
                free(stack);
                return false;
            }
        }
    }

    bool result = (top == 0);
    free(stack);
    return result;
}

int main(void) {
    printf("%d\n", is_valid_parentheses("()[]{}"));
    printf("%d\n", is_valid_parentheses("([)]"));
    printf("%d\n", is_valid_parentheses(NULL));
    printf("%d\n", is_valid_parentheses("("));
    printf("%d\n", is_valid_parentheses(")"));
    return 0;
}