#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

bool isBalancedExpression(char* expression) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int exprLength = strlen(expression);
    char* stack = (char *) malloc(exprLength * sizeof(char));
    int top = -1;

    if (stack == NULL) {
        printf("Could not allocate memory for stack.\n");
        return false;
    }

    for (int i = 0; i < exprLength; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            if (top < exprLength - 1) {
                stack[++top] = expression[i];
            } else {
                free(stack);
                return false;
            }
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (top == -1) {
                free(stack);
                return false;
            } else if ((expression[i] == ')' && stack[top] != '(') ||
                       (expression[i] == ']' && stack[top] != '[') ||
                       (expression[i] == '}' && stack[top] != '{')) {
                free(stack);
                return false;
            } else {
                top--;
            }
        }
    }
    free(stack);
    return top == -1;
}

int main() {
    char* expression = (char *) malloc(MAX_SIZE * sizeof(char));

    if (expression == NULL) {
        printf("Could not allocate memory for expression.\n");
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