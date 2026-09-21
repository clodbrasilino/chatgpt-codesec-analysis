#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 1024

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char items[MAX_STACK_SIZE];
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
    return s != NULL && s->top == MAX_STACK_SIZE - 1;
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

int pop(Stack *s) {
    if (s == NULL || isEmpty(s)) {
        return 0;
    }
    s->top--;
    return 1;
}

char peek(const Stack *s) {
    if (s == NULL || isEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

int isMatchingPair(char opening, char closing) {
    if (opening == '(' && closing == ')') return 1;
    if (opening == '[' && closing == ']') return 1;
    if (opening == '{' && closing == '}') return 1;
    return 0;
}

int isBalanced(const char *expression) {
    Stack stack;
    
    if (expression == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t expr_len = strlen(expression);
    if (expr_len >= MAX_STACK_SIZE) {
        return 0;
    }
    
    initStack(&stack);
    
    for (size_t i = 0; i < expr_len; i++) {
        char current = expression[i];
        
        if (current == '(' || current == '[' || current == '{') {
            if (!push(&stack, current)) {
                return 0;
            }
        }
        else if (current == ')' || current == ']' || current == '}') {
            if (isEmpty(&stack)) {
                return 0;
            }
            
            char top = peek(&stack);
            if (!isMatchingPair(top, current)) {
                return 0;
            }
            
            if (!pop(&stack)) {
                return 0;
            }
        }
    }
    
    return isEmpty(&stack);
}

int main() {
    char expression1[] = "{[()]}";
    char expression2[] = "{[(])}";
    char expression3[] = "((()))";
    char expression4[] = "((())";
    char expression5[] = "";
    char expression6[] = "a*(b+c)-[d/{e-f}]";
    
    printf("\"%s\" is %s\n", expression1, isBalanced(expression1) ? "balanced" : "not balanced");
    printf("\"%s\" is %s\n", expression2, isBalanced(expression2) ? "balanced" : "not balanced");
    printf("\"%s\" is %s\n", expression3, isBalanced(expression3) ? "balanced" : "not balanced");
    printf("\"%s\" is %s\n", expression4, isBalanced(expression4) ? "balanced" : "not balanced");
    printf("\"%s\" is %s\n", expression5, isBalanced(expression5) ? "balanced" : "not balanced");
    printf("\"%s\" is %s\n", expression6, isBalanced(expression6) ? "balanced" : "not balanced");
    
    return 0;
}