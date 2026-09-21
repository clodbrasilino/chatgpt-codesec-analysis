#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
    if (s != NULL && s->top < MAX_SIZE - 1) {
        s->top++;
        s->items[s->top] = c;
        return 1;
    }
    return 0;
}

char pop(Stack *s) {
    if (s != NULL && s->top >= 0) {
        char c = s->items[s->top];
        s->top--;
        return c;
    }
    return '\0';
}

/* Possible weaknesses found:
 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
 */
int isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '{' && close == '}') return 1;
    if (open == '[' && close == ']') return 1;
    return 0;
}

int isBalanced(const char *expression) {
    Stack stack;
    size_t len;
    size_t i;
    
    if (expression == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(expression);
    if (len >= MAX_SIZE) {
        return 0;
    }
    
    initStack(&stack);
    
    for (i = 0; i < len; i++) {
        char current = expression[i];
        
        if (current == '(' || current == '{' || current == '[') {
            if (isFull(&stack) || !push(&stack, current)) {
                return 0;
            }
        }
        else if (current == ')' || current == '}' || current == ']') {
            if (isEmpty(&stack)) {
                return 0;
            }
            
            char top = pop(&stack);
            if (top == '\0' || !isMatchingPair(top, current)) {
                return 0;
            }
        }
    }
    
    return isEmpty(&stack);
}

int main(void) {
    char *expression = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    
    printf("Enter an expression: ");
    bytes_read = getline(&expression, &buffer_size, stdin);
    
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(expression);
        return 1;
    }
    
    if (bytes_read > 0 && expression[bytes_read - 1] == '\n') {
        expression[bytes_read - 1] = '\0';
        bytes_read--;
    }
    
    if ((size_t)bytes_read >= MAX_SIZE) {
        fprintf(stderr, "Input exceeds maximum allowed length\n");
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