#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

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
    if (s->top >= MAX_SIZE - 1) {
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
    if (s->top < 0) {
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
    if (s->top < 0) {
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
    size_t i;
    size_t len;

    if (expression == NULL) {
        return 0;
    }

    len = strnlen(expression, MAX_SIZE);
    if (len == 0 || len >= MAX_SIZE) {
        return 0;
    }

    initStack(&stack);

    for (i = 0; i < len; i++) {
        char ch = expression[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            if (!push(&stack, ch)) {
                return 0;
            }
        } else if (ch == ')' || ch == '}' || ch == ']') {
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
    char input[MAX_SIZE];
    int result;
    size_t inputLen;

    printf("Enter an expression: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        return 1;
    }

    inputLen = strnlen(input, sizeof(input));
    if (inputLen > 0 && input[inputLen - 1] == '\n') {
        input[inputLen - 1] = '\0';
        inputLen--;
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    if (inputLen == 0) {
        printf("Not Balanced\n");
        return 0;
    }

    result = isBalanced(input);

    if (result) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    return 0;
}