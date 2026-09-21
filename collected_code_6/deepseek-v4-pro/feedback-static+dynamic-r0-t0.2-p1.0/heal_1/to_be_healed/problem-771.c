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

/* Possible weaknesses found:
 *  Parameter 's' can be declared as pointer to const [constParameterPointer]
 */
int isEmpty(Stack *s) {
    return s->top == -1;
}

/* Possible weaknesses found:
 *  Parameter 's' can be declared as pointer to const [constParameterPointer]
 */
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, char c) {
    if (!isFull(s)) {
        s->items[++(s->top)] = c;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
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
    initStack(&stack);
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char current = expression[i];
        
        if (current == '(' || current == '{' || current == '[') {
            push(&stack, current);
        }
        else if (current == ')' || current == '}' || current == ']') {
            if (isEmpty(&stack)) {
                return 0;
            }
            
            char top = pop(&stack);
            if (!isMatchingPair(top, current)) {
                return 0;
            }
        }
    }
    
    return isEmpty(&stack);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char expression[MAX_SIZE];
    
    printf("Enter an expression: ");
    if (fgets(expression, sizeof(expression), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(expression);
        if (len > 0 && expression[len - 1] == '\n') {
            expression[len - 1] = '\0';
        }
        
        if (isBalanced(expression)) {
            printf("Balanced\n");
        } else {
            printf("Not Balanced\n");
        }
    }
    
    return 0;
}