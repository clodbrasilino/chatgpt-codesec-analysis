#include <stdio.h>
#include <stdbool.h>

bool isBalanced(const char *expr, size_t len) {
    if (len == 0) return true;
    int stack[len];
    int top = -1;

    for (int i = 0; i < len; ++i) {
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') {
            if (top + 1 >= (int)len) return false;
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
    printf("%s: %s\n", expr1, isBalanced(expr1, sizeof(expr1) - 1) ? "Balanced" : "Not Balanced");

    const char *expr2 = "([)]";
    printf("%s: %s\n", expr2, isBalanced(expr2, sizeof(expr2) - 1) ? "Balanced" : "Not Balanced");

    const char *expr3 = "((()))";
    printf("%s: %s\n", expr3, isBalanced(expr3, sizeof(expr3) - 1) ? "Balanced" : "Not Balanced");

    const char *expr4 = "({[)]}";
    printf("%s: %s\n", expr4, isBalanced(expr4, sizeof(expr4) - 1) ? "Balanced" : "Not Balanced");

    return 0;
}