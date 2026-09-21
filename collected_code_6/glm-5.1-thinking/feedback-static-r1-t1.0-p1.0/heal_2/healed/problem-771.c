#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool isBalanced(const char *expr, size_t len) {
    if (expr == NULL) {
        return true;
    }

    if (len == 0) {
        return true;
    }

    char *stack = (char *)malloc(len * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    int top = -1;

    for (size_t i = 0; i < len; i++) {
        char ch = expr[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            top++;
            stack[top] = ch;
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == -1) {
                free(stack);
                return false;
            }
            char popped = stack[top];
            top--;
            if ((ch == ')' && popped != '(') ||
                (ch == '}' && popped != '{') ||
                (ch == ']' && popped != '[')) {
                free(stack);
                return false;
            }
        }
    }

    bool balanced = (top == -1);
    free(stack);
    return balanced;
}

int main(void) {
    const char *expressions[] = {
        "([{}])",
        "([)]",
        "((()",
        "",
        NULL
    };

    size_t count = sizeof(expressions) / sizeof(expressions[0]);

    for (size_t i = 0; i < count; i++) {
        const char *current = expressions[i];
        if (current == NULL) {
            printf("NULL expression is Balanced\n");
        } else {
            size_t len = strnlen(current, SIZE_MAX);
            printf("Expression: %s is %s\n", current, isBalanced(current, len) ? "Balanced" : "Not Balanced");
        }
    }

    return 0;
}