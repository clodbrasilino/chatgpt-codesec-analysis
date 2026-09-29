#include <stdio.h>
#include <stdlib.h>

struct Stack {
    char* data;
    int top;
    int capacity;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, char item) {
    if (isFull(stack))
        return;
    stack->data[++stack->top] = item;
}

char pop(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->data[stack->top--];
}

char peek(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->data[stack->top];
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
    struct Stack* stack = createStack(100);
    while (exp[i]) {
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
            push(stack, exp[i]);
        if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
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