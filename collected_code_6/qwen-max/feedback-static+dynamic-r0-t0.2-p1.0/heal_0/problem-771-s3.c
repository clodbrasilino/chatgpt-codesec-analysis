#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isBalanced(char *expression) {
    int length = 0;
    while (expression[length] != '\0') {
        length++;
    }
    char *stack = (char *)malloc(length * sizeof(char));
    if (stack == NULL) {
        return false;
    }
    int top = -1;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            stack[++top] = expression[i];
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (top == -1) {
                free(stack);
                return false;
            }
            char popped = stack[top--];
            if ((expression[i] == ')' && popped != '(') ||
                (expression[i] == ']' && popped != '[') ||
                (expression[i] == '}' && popped != '{')) {
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
    char *expr1 = "([]{})";
    char *expr2 = "([)]";
    char *expr3 = "((()))";
    char *expr4 = "({[)]";

    printf("%s: %s\n", expr1, isBalanced(expr1) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr2, isBalanced(expr2) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr3, isBalanced(expr3) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr4, isBalanced(expr4) ? "Balanced" : "Not Balanced");

    return 0;
}