#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'stack' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}

void push(struct Stack* stack, char item) {
    if (stack->top == stack->capacity - 1) 
        return;
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*stack.array + (sizetype)*stack.top' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    stack->array[++stack->top] = item;
}

char pop(struct Stack* stack) {
    if (stack->top == -1) 
        return -1;
    return stack->array[stack->top--];
}

bool isMatchingPair(char character1, char character2) {
    if (character1 == '(' && character2 == ')')
        return true;
    else
        return false;
}

bool areParenthesesBalanced(char exp[]) {
    int i = 0;
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     */
    struct Stack* stack = createStack(strlen(exp));
    while (exp[i]) {
        if (exp[i] == '(')
            push(stack, exp[i]);
        else if (exp[i] == ')') {
            if (stack->top == -1)
                return false;
            else if (!isMatchingPair(pop(stack), exp[i]))
                return false;
        }
        i++;
    }
    if (stack->top == -1) {
        free(stack->array);
        free(stack);
        return true;
    }
    free(stack->array);
    free(stack);
    return false;
}

int main() {
    char expr[] = "(()())";
    if (areParenthesesBalanced(expr))
        printf("Balanced\n");
    else
        printf("Not Balanced\n");
    return 0;
}