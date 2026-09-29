#include <stdio.h>
#include <stdlib.h>

struct Stack {
    char* data;
    int top;
    int capacity;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));

    if (stack == NULL) 
        return NULL;

    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (char*)malloc(stack->capacity * sizeof(char));

    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }

    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, char item) {
    if (!isFull(stack))
        stack->data[++stack->top] = item;
}

char pop(struct Stack* stack) {
    return isEmpty(stack) ? -1 : stack->data[stack->top--];
}

char peek(struct Stack* stack) {
    return isEmpty(stack) ? -1 : stack->data[stack->top];
}

void freeStack(struct Stack* stack) {
    free(stack->data);
    free(stack);
}

int isMatchingPair(char character1, char character2) {
    return (character1 == '(' && character2 == ')') ||
           (character1 == '{' && character2 == '}') ||
           (character1 == '[' && character2 == ']');
}

int areParenthesisBalanced(char exp[]) {
    int i = 0;
    struct Stack* stack = createStack(100);

    if (stack == NULL)
        return 0;

    while (exp[i]) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
            push(stack, exp[i]);
        if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if (isEmpty(stack) || !isMatchingPair(pop(stack), exp[i])) {
                freeStack(stack);
                return 0;
            }
        }
        i++;
    }

    int balanced = isEmpty(stack);
    freeStack(stack);
    return balanced;
}

int main() {
    char exp[100] = "{()}[]";
    if (areParenthesisBalanced(exp))
        printf("Balanced \n");
    else
        printf("Not Balanced \n");
    return 0;
}