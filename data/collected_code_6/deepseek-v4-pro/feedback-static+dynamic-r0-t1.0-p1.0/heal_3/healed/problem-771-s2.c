#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 1024

typedef struct {
    char *items;
    int top;
    int capacity;
} Stack;

void initStack(Stack *s, int capacity) {
    s->capacity = capacity;
    s->items = (char *)malloc((size_t)capacity * sizeof(char));
    if (s->items != NULL) {
        s->top = -1;
    } else {
        s->top = -1;
    }
}

void freeStack(Stack *s) {
    free(s->items);
    s->items = NULL;
    s->top = -1;
    s->capacity = 0;
}

int isEmpty(const Stack *s) {
    return s->top == -1;
}

int isFull(const Stack *s) {
    return s->top == s->capacity - 1;
}

int push(Stack *s, char c) {
    if (s->items == NULL || isFull(s)) {
        return 0;
    }
    s->items[++(s->top)] = c;
    return 1;
}

int pop(Stack *s) {
    if (s->items == NULL || isEmpty(s)) {
        return 0;
    }
    s->top--;
    return 1;
}

char peek(const Stack *s) {
    if (s->items == NULL || isEmpty(s)) {
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
    if (expression == NULL) {
        return 0;
    }
    
    size_t length = strnlen(expression, MAX_STACK_SIZE + 1);
    if (length > MAX_STACK_SIZE) {
        return 0;
    }
    
    Stack stack;
    initStack(&stack, (int)length);
    
    if (stack.items == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < length; i++) {
        char current = expression[i];
        
        if (current == '(' || current == '[' || current == '{') {
            if (!push(&stack, current)) {
                freeStack(&stack);
                return 0;
            }
        }
        else if (current == ')' || current == ']' || current == '}') {
            if (isEmpty(&stack)) {
                freeStack(&stack);
                return 0;
            }
            
            char top = peek(&stack);
            if (top == '\0') {
                freeStack(&stack);
                return 0;
            }
            
            if (!isMatchingPair(top, current)) {
                freeStack(&stack);
                return 0;
            }
            
            if (!pop(&stack)) {
                freeStack(&stack);
                return 0;
            }
        }
    }
    
    int result = isEmpty(&stack);
    freeStack(&stack);
    return result;
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