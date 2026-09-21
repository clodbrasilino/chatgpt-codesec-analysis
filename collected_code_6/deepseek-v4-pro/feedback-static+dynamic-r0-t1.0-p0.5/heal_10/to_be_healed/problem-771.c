#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char items[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    if (s == NULL) return;
    s->top = -1;
}

int isEmpty(const Stack *s) {
    if (s == NULL) return 1;
    return s->top == -1;
}

int isFull(const Stack *s) {
    if (s == NULL) return 1;
    return s->top >= MAX_SIZE - 1;
}

int push(Stack *s, char c) {
    if (s == NULL) return 0;
    if (s->top >= MAX_SIZE - 1) return 0;
    s->top++;
    s->items[s->top] = c;
    return 1;
}

int pop(Stack *s, char *c) {
    if (s == NULL || c == NULL) return 0;
    if (s->top < 0) return 0;
    *c = s->items[s->top];
    s->top--;
    return 1;
}

/* Possible weaknesses found:
 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
 */
int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int isBalanced(const char *expression) {
    Stack stack;
    size_t len;
    size_t i;
    
    if (expression == NULL) {
        return 0;
    }
    
    initStack(&stack);
    
    len = strnlen(expression, MAX_SIZE);
    if (len >= MAX_SIZE) {
        return 0;
    }
    
    for (i = 0; i < len; i++) {
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

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char expression[MAX_SIZE] = {0};
    size_t len;
    char *result;
    
    printf("Enter an expression: ");
    result = fgets(expression, sizeof(expression), stdin);
    if (result == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    len = strnlen(expression, sizeof(expression));
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
        len--;
    }
    else {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            if (ch == EOF) {
                clearerr(stdin);
                break;
            }
        }
    }
    
    if (len == 0) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    if (strnlen(expression, MAX_SIZE) >= MAX_SIZE) {
        fprintf(stderr, "Expression too long\n");
        return 1;
    }
    
    if (isBalanced(expression)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }
    
    return 0;
}