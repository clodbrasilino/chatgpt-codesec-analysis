#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isBalanced(const char *expression, size_t len) {
    char *stack = (char *)malloc(len * sizeof(char));
    if (!stack) return false;
    int top = -1;

    for (size_t i = 0; i < len; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            if (top + 1 >= (int)len) {
                free(stack);
                return false;
            }
            stack[++top] = expression[i];
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (top == -1) {
                free(stack);
                return false;
            }
            char last = stack[top--];
            if ((expression[i] == ')' && last != '(') ||
                (expression[i] == ']' && last != '[') ||
                (expression[i] == '}' && last != '{')) {
                free(stack);
                return false;
            }
        }
    }

    free(stack);
    return top == -1;
}

int main() {
    const char *expressions[] = {
        "([]{})",
        "([)]",
        "{[()]}",
        "{[(])}",
        "{{[[(())]]}}",
        "(()"
    };

    for (size_t i = 0; i < sizeof(expressions) / sizeof(expressions[0]); i++) {
        size_t len = strlen(expressions[i]);
        printf("%s: %s\n", expressions[i], isBalanced(expressions[i], len) ? "Balanced" : "Not Balanced");
    }

    return 0;
}