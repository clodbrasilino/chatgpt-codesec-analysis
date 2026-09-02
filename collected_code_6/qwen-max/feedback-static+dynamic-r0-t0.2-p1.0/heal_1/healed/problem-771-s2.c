#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isBalanced(const char *expression) {
    int len = 0;
    while (expression[len] != '\0') len++;
    if (len % 2 != 0) return false;

    char stack[len + 1];
    int top = -1;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            if (top >= len - 1) return false;
            stack[++top] = expression[i];
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (top == -1) return false;
            if ((expression[i] == ')' && stack[top] == '(') ||
                (expression[i] == ']' && stack[top] == '[') ||
                (expression[i] == '}' && stack[top] == '{')) {
                top--;
            } else {
                return false;
            }
        }
    }

    return top == -1;
}

int main() {
    const char *expr1 = "([]{})";
    const char *expr2 = "([)]";
    const char *expr3 = "((()))";
    const char *expr4 = "({[()]})";
    const char *expr5 = "({[)]}";

    printf("%s: %s\n", expr1, isBalanced(expr1) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr2, isBalanced(expr2) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr3, isBalanced(expr3) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr4, isBalanced(expr4) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr5, isBalanced(expr5) ? "Balanced" : "Not Balanced");

    return 0;
}