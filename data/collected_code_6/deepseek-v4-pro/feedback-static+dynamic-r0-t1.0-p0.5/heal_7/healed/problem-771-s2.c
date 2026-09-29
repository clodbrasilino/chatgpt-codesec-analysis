#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    if (s != NULL) {
        s->top = -1;
    }
}

int isEmpty(const Stack *s) {
    if (s == NULL) {
        return 1;
    }
    return s->top == -1;
}

int isFull(const Stack *s) {
    if (s == NULL) {
        return 1;
    }
    return s->top >= MAX_SIZE - 1;
}

int push(Stack *s, char c) {
    if (s == NULL) {
        return 0;
    }
    if (s->top < -1) {
        s->top = -1;
    }
    if (isFull(s)) {
        return 0;
    }
    s->top++;
    s->items[s->top] = c;
    return 1;
}

int pop(Stack *s, char *c) {
    if (s == NULL || c == NULL) {
        return 0;
    }
    if (isEmpty(s)) {
        return 0;
    }
    if (s->top < 0 || s->top >= MAX_SIZE) {
        return 0;
    }
    *c = s->items[s->top];
    s->top--;
    return 1;
}

int isMatchingPair(char opening, char closing) {
    if (opening == '(' && closing == ')') return 1;
    if (opening == '{' && closing == '}') return 1;
    if (opening == '[' && closing == ']') return 1;
    return 0;
}

int isBalanced(const char *expression) {
    if (expression == NULL) {
        return 0;
    }
    
    Stack stack;
    initStack(&stack);
    
    size_t len = strlen(expression);
    
    for (size_t i = 0; i < len && i < MAX_SIZE; i++) {
        char current = expression[i];
        
        if (current == '(' || current == '{' || current == '[') {
            if (!push(&stack, current)) {
                return 0;
            }
        }
        else if (current == ')' || current == '}' || current == ']') {
            char topChar;
            if (!pop(&stack, &topChar)) {
                return 0;
            }
            if (!isMatchingPair(topChar, current)) {
                return 0;
            }
        }
    }
    
    return isEmpty(&stack);
}

int main(void) {
    char *expression = NULL;
    size_t bufferSize = 0;
    ssize_t bytesRead;
    
    printf("Enter an expression: ");
    bytesRead = getline(&expression, &bufferSize, stdin);
    
    if (bytesRead == -1) {
        fprintf(stderr, "Error reading input\n");
        free(expression);
        return 1;
    }
    
    if (bytesRead > 0 && expression[bytesRead - 1] == '\n') {
        expression[bytesRead - 1] = '\0';
        bytesRead--;
    }
    
    if (bytesRead == 0) {
        fprintf(stderr, "Empty expression\n");
        free(expression);
        return 1;
    }
    
    if ((size_t)bytesRead > MAX_SIZE) {
        fprintf(stderr, "Expression too long\n");
        free(expression);
        return 1;
    }
    
    if (isBalanced(expression)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }
    
    free(expression);
    return 0;
}