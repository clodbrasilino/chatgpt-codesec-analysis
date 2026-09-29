#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

bool isBalancedExpression(char* expression) {
    if(expression == NULL) {
        return false;
    }
    int exprLength = strlen(expression);
    char* stack = (char *) calloc((exprLength+1), sizeof(char));
    if (stack == NULL) {
        return false;
    }
    int top = -1;

    for (int i = 0; i < exprLength; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            stack[++top] = expression[i];
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (top == -1 ||
                (expression[i] == ')' && stack[top] != '(') ||
                (expression[i] == ']' && stack[top] != '[') ||
                (expression[i] == '}' && stack[top] != '{')) {
                free(stack);
                return false;
            }
            top--;
        }
    }
    free(stack);
    return top == -1;
}

int main() {
    char* expression = (char *) calloc(MAX_SIZE, sizeof(char));
    if (expression == NULL) {
        return 1;
    }

    printf("Enter expression: ");
    fgets(expression, MAX_SIZE, stdin);
    expression[strcspn(expression, "\n")] = 0;

    if (isBalancedExpression(expression)) {
        printf("The expression is balanced.\n");
    } else {
        printf("The expression is not balanced.\n");
    }

    free(expression);
    return 0;
}