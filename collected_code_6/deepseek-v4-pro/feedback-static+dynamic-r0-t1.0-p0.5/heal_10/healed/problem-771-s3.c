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
    if (s->top >= 0 && s->top < MAX_SIZE) {
        *c = s->items[s->top];
        s->top--;
        return 1;
    }
    return 0;
}

int isMatchingPair(char opening, char closing) {
    if (opening == '(' && closing == ')') return 1;
    if (opening == '{' && closing == '}') return 1;
    if (opening == '[' && closing == ']') return 1;
    return 0;
}

int isBalanced(const char *expression) {
    Stack stack;
    size_t i = 0;
    size_t length;
    
    if (expression == NULL) {
        return 0;
    }
    
    length = strnlen(expression, MAX_SIZE);
    if (length >= MAX_SIZE) {
        return 0;
    }
    
    initStack(&stack);
    
    while (i < length && expression[i] != '\0') {
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
        i++;
    }
    
    return isEmpty(&stack);
}

int main(void) {
    char expression[MAX_SIZE + 2];
    char *newlinePos;
    size_t inputLen;
    size_t i;
    
    for (i = 0; i < sizeof(expression); i++) {
        expression[i] = '\0';
    }
    
    printf("Enter an expression: ");
    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    newlinePos = strchr(expression, '\n');
    if (newlinePos == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    *newlinePos = '\0';
    
    inputLen = strlen(expression);
    if (inputLen >= MAX_SIZE) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (isBalanced(expression)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }
    
    return EXIT_SUCCESS;
}