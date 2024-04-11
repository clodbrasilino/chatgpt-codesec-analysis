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

int isValid(char* str) {
    int n = strlen(str);
    Stack* stack = createStack(n);
    for (int i = 0; i < n; i++) {
        if (str[i] == '(') {
            push(stack, str[i]);
        } else if (str[i] == ')') {
            if (isEmpty(stack)) {
                return 0;
            } else {
                pop(stack);
            }
        }
    }
    return isEmpty(stack);
}

int main() {
    char str[] = "((()))";
    if (isValid(str)) {
        printf("Valid\n");
    } else {
        printf("Not Valid\n");
    }
    return 0;
}