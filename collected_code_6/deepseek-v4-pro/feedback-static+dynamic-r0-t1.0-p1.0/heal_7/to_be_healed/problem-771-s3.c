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

int peek(const Stack *s, char *c) {
    if (s == NULL || c == NULL) {
        return 0;
    }
    if (isEmpty(s)) {
        return 0;
    }
    *c = s->items[s->top];
    return 1;
}

int isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

int isBalanced(const char *expression) {
    Stack stack;
    size_t len;
    size_t i;

    if (expression == NULL) {
        return 0;
    }

    len = strnlen(expression, MAX_SIZE + 1);
    if (len >= MAX_SIZE) {
        return 0;
    }

    initStack(&stack);

    for (i = 0; i < len; i++) {
        char c = expression[i];

        if (c == '(' || c == '{' || c == '[') {
            if (!push(&stack, c)) {
                return 0;
            }
        } else if (c == ')' || c == '}' || c == ']') {
            char topChar;
            if (!pop(&stack, &topChar)) {
                return 0;
            }
            if (!isMatchingPair(topChar, c)) {
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
    char input[MAX_SIZE + 1];
    int result;
    size_t len;
    size_t i;

    printf("Enter an expression: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        while (c != '\n' && c != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            c = getchar();
        }
    }

    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] != '(' && input[i] != ')' && 
            input[i] != '{' && input[i] != '}' && 
            input[i] != '[' && input[i] != ']') {
            continue;
        }
    }

    result = isBalanced(input);

    if (result) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    return 0;
}