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
    if (s == NULL) {
        return 0;
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
    Stack stack;
    size_t i;
    size_t len;
    
    if (expression == NULL) {
        return 0;
    }
    
    len = strnlen(expression, MAX_SIZE + 1);
    if (len == 0 || len > MAX_SIZE) {
        return 0;
    }
    
    initStack(&stack);
    
    for (i = 0; i < len; i++) {
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
    char *input = NULL;
    size_t bufferSize = 0;
    ssize_t lineLength;
    
    printf("Enter an expression: ");
    
    lineLength = getline(&input, &bufferSize, stdin);
    
    if (lineLength == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    
    if (lineLength > 0 && input[lineLength - 1] == '\n') {
        input[lineLength - 1] = '\0';
        lineLength--;
    }
    
    if ((size_t)lineLength > MAX_SIZE) {
        fprintf(stderr, "Expression exceeds maximum allowed length\n");
        free(input);
        return 1;
    }
    
    if (isBalanced(input)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }
    
    free(input);
    return 0;
}