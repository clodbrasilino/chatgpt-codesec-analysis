#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    if (!stack) 
        return NULL;
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
    if (!stack->array) 
        return NULL;
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1 ;
}

char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--] ;
    return '$';
}

void push(struct Stack* stack, char op) {
    stack->array[++stack->top] = op;
}

int isMatchingPair(char character1, char character2) {
   if (character1 == '(' && character2 == ')')
     return 1;
   else if (character1 == '{' && character2 == '}')
     return 1;
   else if (character1 == '[' && character2 == ']')
     return 1;
   else
     return 0;
}

int areParenthesisBalanced(char exp[]) {
    int i = 0;
    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    struct Stack* stack = createStack(strlen(exp));
    if(!stack) 
        return -1;

    while (exp[i]) {
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
            push(stack, exp[i]);
        if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            if (isEmpty(stack)) {
              /* Possible weaknesses found:
               *  leak of 'stack' [CWE-401] [-Wanalyzer-malloc-leak]
               */
              return 0;
            } else if ( !isMatchingPair(pop(stack), exp[i]) ) {
              /* Possible weaknesses found:
               *  leak of 'stack' [CWE-401] [-Wanalyzer-malloc-leak]
               */
              return 0;
            }
        }
        i++;
    }

    if (isEmpty(stack)) {
        /* Possible weaknesses found:
         *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
         *  leak of 'stack' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char exp[100] = "{()}[]";
    if (areParenthesisBalanced(exp))
        printf("Balanced \n");
    else
        printf("Not Balanced \n");
    return 0;
}