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
    initStack(&stack);
    
    for (size_t i = 0; expression[i] != '\0'; i++) {
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
    
    printf("Enter an expression: ");
    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }
    else {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
    
    if (expression[0] == '\0') {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    if (isBalanced(expression)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }
    
    return 0;
}