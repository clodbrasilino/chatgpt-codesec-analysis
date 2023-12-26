#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Function to check if the given expression is balanced or not
bool isBalancedExpression(char expression[]) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char stack[MAX_SIZE];
    int top = -1;

    /* Possible weaknesses found:
     *  Cannot determine that 'expression[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; expression[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'expression[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            /* Possible weaknesses found:
             *  Cannot determine that 'expression[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            stack[++top] = expression[i];
        }
        /* Possible weaknesses found:
         *  Cannot determine that 'expression[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (top == -1) {
                return false;
            }
            /* Possible weaknesses found:
             *  Cannot determine that 'stack[top]' is initialized [premium-bughuntingUninit]
             *  Cannot determine that 'expression[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            else if ((expression[i] == ')' && stack[top] != '(') ||
                     /* Possible weaknesses found:
                      *  Cannot determine that 'stack[top]' is initialized [premium-bughuntingUninit]
                      *  Cannot determine that 'expression[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                      */
                     (expression[i] == ']' && stack[top] != '[') ||
                     /* Possible weaknesses found:
                      *  Cannot determine that 'stack[top]' is initialized [premium-bughuntingUninit]
                      *  Cannot determine that 'expression[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                      */
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
    /* Possible weaknesses found:
     *  Cannot determine that 'expression[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(expression, MAX_SIZE, stdin);

    if (isBalancedExpression(expression)) {
        printf("The expression is balanced.\n");
    }
    else {
        printf("The expression is not balanced.\n");
    }

    return 0;
}