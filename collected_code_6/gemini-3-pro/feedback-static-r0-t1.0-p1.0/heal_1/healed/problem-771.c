#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct StackNode {
    char data;
    struct StackNode* next;
};

struct StackNode* createNode(char data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

bool push(struct StackNode** root, char data) {
    struct StackNode* newNode = createNode(data);
    if (!newNode) {
        return false;
    }
    newNode->next = *root;
    *root = newNode;
    return true;
}

char pop(struct StackNode** root) {
    if (*root == NULL) {
        return '\0';
    }
    struct StackNode* temp = *root;
    *root = (*root)->next;
    char popped = temp->data;
    free(temp);
    return popped;
}

void freeStack(struct StackNode** root) {
    while (*root != NULL) {
        pop(root);
    }
}

bool isMatchingPair(char character1, char character2) {
    if (character1 == '(' && character2 == ')') return true;
    if (character1 == '{' && character2 == '}') return true;
    if (character1 == '[' && character2 == ']') return true;
    return false;
}

bool isBalanced(const char* exp) {
    if (exp == NULL) {
        return false;
    }

    struct StackNode* stack = NULL;
    
    for (size_t i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[') {
            if (!push(&stack, exp[i])) {
                freeStack(&stack);
                return false;
            }
        }
        else if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            if (stack == NULL) {
                return false;
            }
            char popped = pop(&stack);
            if (!isMatchingPair(popped, exp[i])) {
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
    const char* exp1 = "{[()]}";
    const char* exp2 = "{[(])}";
    
    if (isBalanced(exp1)) {
        printf("Expression 1 is balanced\n");
    } else {
        printf("Expression 1 is not balanced\n");
    }
    
    if (isBalanced(exp2)) {
        printf("Expression 2 is balanced\n");
    } else {
        printf("Expression 2 is not balanced\n");
    }
    
    return 0;
}