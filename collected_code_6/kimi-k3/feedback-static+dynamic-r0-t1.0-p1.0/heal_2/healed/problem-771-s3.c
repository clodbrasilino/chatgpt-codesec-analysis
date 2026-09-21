#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char *items;
    int top;
    size_t capacity;
} Stack;

int initStack(Stack *s, size_t capacity) {
    if (s == NULL || capacity == 0) {
        return 0;
    }
    s->items = (char *)malloc(capacity * sizeof(char));
    if (s->items == NULL) {
        return 0;
    }
    s->top = -1;
    s->capacity = capacity;
    return 1;
}

void freeStack(Stack *s) {
    if (s != NULL) {
        free(s->items);
        s->items = NULL;
        s->top = -1;
        s->capacity = 0;
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
    return (size_t)(s->top) >= s->capacity - 1;
}

int push(Stack *s, char c) {
    if (s == NULL || isFull(s)) {
        return 0;
    }
    s->items[++(s->top)] = c;
    return 1;
}

char pop(Stack *s) {
    if (s == NULL || isEmpty(s)) {
        return '\0';
    }
    return s->items[(s->top)--];
}

int isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

int isBalanced(const char *expression) {
    Stack stack;
    size_t i;
    size_t len;
    int result;
    
    if (expression == NULL) {
        return 0;
    }
    
    len = strnlen(expression, MAX_SIZE);
    if (len >= MAX_SIZE) {
        return 0;
    }
    
    if (!initStack(&stack, len + 1)) {
        return 0;
    }
    
    for (i = 0; i < len; i++) {
        char current = expression[i];
        
        if (current == '(' || current == '{' || current == '[') {
            if (!push(&stack, current)) {
                freeStack(&stack);
                return 0;
            }
        } else if (current == ')' || current == '}' || current == ']') {
            char top_char;
            
            if (isEmpty(&stack)) {
                freeStack(&stack);
                return 0;
            }
            
            top_char = pop(&stack);
            if (!isMatchingPair(top_char, current)) {
                freeStack(&stack);
                return 0;
            }
        }
    }
    
    result = isEmpty(&stack);
    freeStack(&stack);
    return result;
}

int main(void) {
    char *expression = NULL;
    size_t buffer_size = MAX_SIZE;
    ssize_t len;
    
    printf("Enter an expression: ");
    
    expression = (char *)malloc(buffer_size * sizeof(char));
    if (expression == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    len = getline(&expression, &buffer_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(expression);
        return EXIT_FAILURE;
    }
    
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }
    
    if (isBalanced(expression)) {
        printf("The expression is balanced.\n");
    } else {
        printf("The expression is not balanced.\n");
    }
    
    free(expression);
    return EXIT_SUCCESS;
}