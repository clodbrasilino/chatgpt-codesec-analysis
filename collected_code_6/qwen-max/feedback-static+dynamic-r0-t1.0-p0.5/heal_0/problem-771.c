#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isBalanced(const char *expr) {
    int len = strlen(expr);
    int stack[len];
    int top = -1;

    for (int i = 0; i < len; ++i) {
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') {
            if (top + 1 >= len) return false;
            stack[++top] = expr[i];
        } else if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}') {
            if (top == -1) return false;
            char c = stack[top--];
            if ((expr[i] == ')' && c != '(') ||
                (expr[i] == ']' && c != '[') ||
                (expr[i] == '}' && c != '{')) {
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
    const char *expr4 = "({[)]}";

    printf("%s: %s\n", expr1, isBalanced(expr1) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr2, isBalanced(expr2) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr3, isBalanced(expr3) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr4, isBalanced(expr4) ? "Balanced" : "Not Balanced");

    return 0;
}