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
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'stack' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
    /* Possible weaknesses found:
     *  leak of 'stack' [CWE-401] [-Wanalyzer-malloc-leak]
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return stack->top == -1;
}

void push(Stack* stack, char item) {
    if (isFull(stack))
        return;
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*stack.array + (sizetype)*stack.top' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    stack->array[++stack->top] = item;
}

char pop(Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

int isValid(char* s) {
    int n = strlen(s);
    Stack* stack = createStack(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            push(stack, s[i]);
        } else if (s[i] == ')') {
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
    char s[100];
    printf("Enter a string of parentheses: ");
    scanf("%s", s);
    if (isValid(s)) {
        printf("The string is valid.\n");
    } else {
        printf("The string is not valid.\n");
    }
    return 0;
}