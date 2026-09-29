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
    size_t i = 0;
    
    if (expression == NULL) {
        return 0;
    }
    
    if (strlen(expression) > MAX_SIZE) {
        return 0;
    }
    
    initStack(&stack);
    
    while (expression[i] != '\0') {
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
    char expression[MAX_SIZE + 2] = {0};
    char *newlinePos;
    size_t inputLen;
    
    printf("Enter an expression: ");
    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    inputLen = strlen(expression);
    if (inputLen == sizeof(expression) - 1 && expression[inputLen - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    newlinePos = strchr(expression, '\n');
    if (newlinePos != NULL) {
        *newlinePos = '\0';
    }
    
    if (isBalanced(expression)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }
    
    return EXIT_SUCCESS;
}