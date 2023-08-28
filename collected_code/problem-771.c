#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Function to check if the given expression is balanced or not
bool isBalancedExpression(char expression[]) {
    char stack[MAX_SIZE];
    int top = -1;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            stack[++top] = expression[i];
        }
        else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (top == -1) {
                return false;
            }
            else if ((expression[i] == ')' && stack[top] != '(') ||
                     (expression[i] == ']' && stack[top] != '[') ||
                     (expression[i] == '}' && stack[top] != '{')) {
                return false;
            }
            else {
                top--;
            }
        }
    }

    return top == -1;
}

int main() {
    char expression[MAX_SIZE];

    printf("Enter expression: ");
    fgets(expression, MAX_SIZE, stdin);

    if (isBalancedExpression(expression)) {
        printf("The expression is balanced.\n");
    }
    else {
        printf("The expression is not balanced.\n");
    }

    return 0;
}