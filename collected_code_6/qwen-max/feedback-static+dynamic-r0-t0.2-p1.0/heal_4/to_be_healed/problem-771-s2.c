#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isBalanced(const char *expression) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(expression);
    if (len % 2 != 0) return false;

    char *stack = (char *)malloc((len + 1) * sizeof(char));
    if (stack == NULL) return false;
    int top = -1;

    for (size_t i = 0; i < len; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            if (top >= (int)len - 1) { free(stack); return false; }
            stack[++top] = expression[i];
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (top == -1) { free(stack); return false; }
            if ((expression[i] == ')' && stack[top] == '(') ||
                (expression[i] == ']' && stack[top] == '[') ||
                (expression[i] == '}' && stack[top] == '{')) {
                top--;
            } else {
                free(stack);
                return false;
            }
        }
    }

    bool result = (top == -1);
    free(stack);
    return result;
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