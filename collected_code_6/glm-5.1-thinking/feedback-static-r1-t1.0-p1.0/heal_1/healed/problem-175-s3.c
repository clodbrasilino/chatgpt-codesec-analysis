#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_valid_parentheses(const char *str, size_t len) {
    if (str == NULL) {
        return false;
    }

    char *stack = len > 0 ? malloc(len) : NULL;
    if (len > 0 && stack == NULL) {
        return false;
    }

    size_t top = 0;
    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        if (c == '\0') {
            break;
        }
        if (c == '(' || c == '{' || c == '[') {
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                free(stack);
                return false;
            }
            char popped = stack[--top];
            if ((c == ')' && popped != '(') ||
                (c == '}' && popped != '{') ||
                (c == ']' && popped != '[')) {
                free(stack);
                return false;
            }
        }
    }

    bool is_valid = (top == 0);
    free(stack);
    return is_valid;
}

int main(void) {
    printf("%d\n", is_valid_parentheses("()[]{}", sizeof("()[]{}") - 1));
    printf("%d\n", is_valid_parentheses("([{}])", sizeof("([{}])") - 1));
    printf("%d\n", is_valid_parentheses("(]", sizeof("(]") - 1));
    printf("%d\n", is_valid_parentheses("([)]", sizeof("([)]") - 1));
    printf("%d\n", is_valid_parentheses("", sizeof("") - 1));
    printf("%d\n", is_valid_parentheses(NULL, 0));
    return 0;
}