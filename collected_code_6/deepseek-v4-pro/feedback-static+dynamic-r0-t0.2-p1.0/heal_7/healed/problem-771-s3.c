#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

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
    return s != NULL && s->top == -1;
}

int isFull(const Stack *s) {
    return s != NULL && s->top == MAX_SIZE - 1;
}

int push(Stack *s, char c) {
    if (s == NULL || isFull(s)) {
        return 0;
    }
    s->top++;
    s->items[s->top] = c;
    return 1;
}

int pop(Stack *s, char *c) {
    if (s == NULL || c == NULL || isEmpty(s)) {
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
    size_t length;
    
    if (expression == NULL) {
        return 0;
    }
    
    length = strnlen(expression, MAX_SIZE + 1);
    if (length > MAX_SIZE) {
        return 0;
    }
    
    initStack(&stack);
    
    for (i = 0; i < length && expression[i] != '\0'; i++) {
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
    char expression[MAX_SIZE + 1];
    char *result;
    size_t len;
    int c;
    
    printf("Enter an expression: ");
    result = fgets(expression, sizeof(expression), stdin);
    if (result == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    len = strnlen(expression, sizeof(expression));
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return 1;
    }
    
    if (expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
        len--;
    }
    else {
        if (len == sizeof(expression) - 1) {
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            fprintf(stderr, "Input too long\n");
            return 1;
        }
    }
    
    if (len > MAX_SIZE) {
        fprintf(stderr, "Input exceeds allowed length\n");
        return 1;
    }
    
    if (isBalanced(expression)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }
    
    return 0;
}