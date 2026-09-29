#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(const Stack *s) {
    return s->top == -1;
}

int isFull(const Stack *s) {
    return s->top == MAX_SIZE - 1;
}

int push(Stack *s, char c) {
    if (isFull(s)) {
        return 0;
    }
    s->items[++(s->top)] = c;
    return 1;
}

int pop(Stack *s, char *c) {
    if (isEmpty(s)) {
        return 0;
    }
    *c = s->items[(s->top)--];
    return 1;
}

int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int isBalanced(const char *expression) {
    Stack stack;
    initStack(&stack);
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        
        if (ch == '(' || ch == '{' || ch == '[') {
            if (!push(&stack, ch)) {
                return 0;
            }
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            char topChar;
            if (!pop(&stack, &topChar)) {
                return 0;
            }
            if (!isMatchingPair(topChar, ch)) {
                return 0;
            }
        }
    }
    
    return isEmpty(&stack);
}

int main() {
    char expression[MAX_SIZE];
    
    printf("Enter an expression: ");
    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }
    
    if (isBalanced(expression)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }
    
    return 0;
}