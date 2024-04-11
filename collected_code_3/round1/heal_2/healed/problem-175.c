#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct Stack {
    int top;
    unsigned capacity;
    char* array;
} Stack;

Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    if(!stack) return NULL; 

    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));

    if(!stack->array){
        free(stack);
        return NULL;
    }

    return stack;
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char item) {
    if (!stack || isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

char pop(Stack* stack) {
    if (!stack || isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

int isMatchingPair(char character1, char character2) {
    return character1 == '(' && character2 == ')';
}

int areParenthesisBalanced(char exp[]) {
    int i = 0;
    Stack* stack = createStack(strlen(exp));
    if(!stack) return 0; 

    while (exp[i]) {
        if (exp[i] == '(')
            push(stack, exp[i]);
        else if (exp[i] == ')') {
            if (isEmpty(stack) || !isMatchingPair(pop(stack), exp[i])){
                free(stack->array);
                free(stack);
                return 0;
            }
        }
        i++;
    }

    int empty = isEmpty(stack);
    free(stack->array);
    free(stack);
    return empty;
}

int main() {
    char exp[MAX_SIZE];
    printf("Enter an expression: ");
    fgets(exp, MAX_SIZE, stdin);
    if (areParenthesisBalanced(exp))
        printf("Balanced \n");
    else
        printf("Not Balanced \n");
    return 0;
}