#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

struct Stack {
    int top;
    char values[MAX_SIZE];
};

void initStack(struct Stack* stack) {
    stack->top = -1;
}

void push(struct Stack* stack, char c) {
    if (stack->top >= (MAX_SIZE - 1)) {
        return;
    }
    stack->top++;
    stack->values[stack->top] = c;
}

void pop(struct Stack* stack) {
    if (stack->top < 0) {
        return;
    }
    stack->top--;
}

char peek(struct Stack* stack) {
    if (stack->top < 0) {
        return '\0';
    }
    return stack->values[stack->top];
}

int validParentheses(const char *inputStr) {
    struct Stack stack;
    initStack(&stack);

    int length = strlen(inputStr);
    for (int i = 0; i < length; i++) {
        if (inputStr[i] == '(') {
            push(&stack, '(');
        } else if (inputStr[i] == ')') {
            if (peek(&stack) == '(') {
                pop(&stack);
            } else {
                return 0;
            }
        }
    }

    return stack.top == -1 ? 1 : 0;
}

int main() {
    char *testInput1 = "((()))";
    char *testInput2 = "(()))";

    printf("%s is %s\n", testInput1, validParentheses(testInput1) ? "valid" : "invalid");
    printf("%s is %s\n", testInput2, validParentheses(testInput2) ? "valid" : "invalid");

    return 0;
}