#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

void push(Node** top, char data) {
    if (top == NULL) {
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

char pop(Node** top) {
    if (top == NULL || *top == NULL) {
        return '\0';
    }
    Node* temp = *top;
    char data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

bool isMatchingPair(char character1, char character2) {
    if (character1 == '(' && character2 == ')') {
        return true;
    } else if (character1 == '{' && character2 == '}') {
        return true;
    } else if (character1 == '[' && character2 == ']') {
        return true;
    }
    return false;
}

bool isBalanced(const char* expression) {
    if (expression == NULL) {
        return false;
    }

    Node* stack = NULL;

    for (size_t i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '{' || expression[i] == '(' || expression[i] == '[') {
            push(&stack, expression[i]);
        } else if (expression[i] == '}' || expression[i] == ')' || expression[i] == ']') {
            if (stack == NULL) {
                return false;
            }
            char poppedChar = pop(&stack);
            if (!isMatchingPair(poppedChar, expression[i])) {
                while (stack != NULL) {
                    pop(&stack);
                }
                return false;
            }
        }
    }

    if (stack == NULL) {
        return true;
    } else {
        while (stack != NULL) {
            pop(&stack);
        }
        return false;
    }
}

int main(void) {
    const char* expr1 = "{[()]}";
    const char* expr2 = "{[(])}";
    const char* expr3 = "{{[[(())]]}}";

    if (isBalanced(expr1)) {
        printf("Expression 1 is balanced\n");
    } else {
        printf("Expression 1 is not balanced\n");
    }

    if (isBalanced(expr2)) {
        printf("Expression 2 is balanced\n");
    } else {
        printf("Expression 2 is not balanced\n");
    }

    if (isBalanced(expr3)) {
        printf("Expression 3 is balanced\n");
    } else {
        printf("Expression 3 is not balanced\n");
    }

    return EXIT_SUCCESS;
}