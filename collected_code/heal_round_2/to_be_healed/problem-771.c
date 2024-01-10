#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

bool isBalancedExpression(char* expression) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char stack[MAX_SIZE];
    int i;
    int top = -1;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    for (i = 0; i < strlen(expression); i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            if (top < MAX_SIZE - 1) {
                stack[++top] = expression[i];
            } else {
                return false;
            }
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char expression[MAX_SIZE];

    printf("Enter expression: ");
    fgets(expression, MAX_SIZE, stdin);
    expression[strcspn(expression, "\n")] = 0;

    if (isBalancedExpression(expression)) {
        printf("The expression is balanced.\n");
    }
    else {
        printf("The expression is not balanced.\n");
    }

    return 0;
}