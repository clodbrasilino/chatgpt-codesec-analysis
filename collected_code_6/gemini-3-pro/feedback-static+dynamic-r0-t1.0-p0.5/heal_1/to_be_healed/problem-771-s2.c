#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

void freeStack(Node** top) {
    if (top == NULL) {
        return;
    }
    while (*top != NULL) {
        pop(top);
    }
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(expression);

    for (size_t i = 0; i < len; i++) {
        if (expression[i] == '{' || expression[i] == '(' || expression[i] == '[') {
            push(&stack, expression[i]);
        } else if (expression[i] == '}' || expression[i] == ')' || expression[i] == ']') {
            if (stack == NULL) {
                return false;
            }
            char poppedChar = pop(&stack);
            if (!isMatchingPair(poppedChar, expression[i])) {
                freeStack(&stack);
                return false;
            }
        }
    }

    bool balanced = (stack == NULL);
    freeStack(&stack);
    return balanced;
}

int main(void) {
    const char* expr1 = "{[()]}";
    const char* expr2 = "{[(])}";
    const char* expr3 = "{{[[(())]]}}";
    const char* expr4 = "";
    const char* expr5 = NULL;

    printf("%s\n", isBalanced(expr1) ? "Balanced" : "Not Balanced");
    printf("%s\n", isBalanced(expr2) ? "Balanced" : "Not Balanced");
    printf("%s\n", isBalanced(expr3) ? "Balanced" : "Not Balanced");
    printf("%s\n", isBalanced(expr4) ? "Balanced" : "Not Balanced");
    /* Possible weaknesses found:
     *  Condition 'isBalanced(expr5)' is always false [knownConditionTrueFalse]
     *  Calling function 'isBalanced' returns 0
     *  Condition 'isBalanced(expr5)' is always false
     */
    printf("%s\n", isBalanced(expr5) ? "Balanced" : "Not Balanced");

    return 0;
}