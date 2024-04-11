#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    int top;
    unsigned capacity;
    char* array;
} Stack;

Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

char pop(Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

int isMatchingPair(char character1, char character2) {
    if (character1 == '(' && character2 == ')')
        return 1;
    else
        return 0;
}

int areParenthesisBalanced(char exp[]) {
    int i = 0;
    Stack* stack = createStack(strlen(exp));
    while (exp[i]) {
        if (exp[i] == '(')
            push(stack, exp[i]);
        if (exp[i] == ')') {
            if (isEmpty(stack)) {
                return 0;
            } else if (!isMatchingPair(pop(stack), exp[i])) {
                return 0;
            }
        }
        i++;
    }
    if (isEmpty(stack))
        return 1;
    else
        return 0;
}

int main() {
    char exp[100] = "{()}[]";
    if (areParenthesisBalanced(exp))
        printf("Balanced \n");
    else
        printf("Not Balanced \n");
    return 0;
}