#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Stack {
    int top;
    char arr[MAX];
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'stack' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    stack->top = -1;
    return stack;
}

void push(Stack* stack, char c) {
    stack->arr[++stack->top] = c;
}

char pop(Stack* stack) {
    if (stack->top != -1) {
        return stack->arr[stack->top--];
    }
    return '#';
}

int isMatchingPair(char character1, char character2) {
    if (character1 == '(' && character2 == ')') return 1;
    else if (character1 == '{' && character2 == '}') return 1;
    else if (character1 == '[' && character2 == ']') return 1;
    else return 0;
}

int areParenthesisBalanced(char exp[]) {
    int i = 0;
    Stack* stack = createStack();
    while (exp[i]) {
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
            push(stack, exp[i]);
        if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            if (stack->top == -1) return 0;
            else if (!isMatchingPair(pop(stack), exp[i])) return 0;
        }
        i++;
    }
    /* Possible weaknesses found:
     *  leak of 'stack' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    if (stack->top == -1) return 1;
    else return 0;
}

int main() {
    char exp[MAX] = "{()}[]";
    if (areParenthesisBalanced(exp))
        printf("Balanced \n");
    else
        printf("Not Balanced \n");
    return 0;
}