#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int isBalanced(const char *expr) {
    if (expr == NULL) {
        return 0;
    }

    size_t len = strnlen(expr, SIZE_MAX);
    
    if (len == 0) {
        return 1;
    }

    char *stack = malloc(len * sizeof(char));
    if (stack == NULL) {
        return 0;
    }

    int top = -1;

    for (size_t i = 0; i < len; i++) {
        char ch = expr[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            top++;
            stack[top] = ch;
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (top == -1) {
                free(stack);
                return 0;
            }
            char match = stack[top];
            top--;
            if ((ch == ')' && match != '(') ||
                (ch == ']' && match != '[') ||
                (ch == '}' && match != '{')) {
                free(stack);
                return 0;
            }
        }
    }

    int balanced = (top == -1) ? 1 : 0;
    free(stack);
    return balanced;
}

int main(int argc, char *argv[]) {
    const char *expr1 = "([{}])";
    const char *expr2 = "([)]";
    const char *expr3 = "(((()";
    const char *expr4 = NULL;

    printf("Expression 1: %d\n", isBalanced(expr1));
    printf("Expression 2: %d\n", isBalanced(expr2));
    printf("Expression 3: %d\n", isBalanced(expr3));
    printf("Expression 4: %d\n", isBalanced(expr4));

    return 0;
}