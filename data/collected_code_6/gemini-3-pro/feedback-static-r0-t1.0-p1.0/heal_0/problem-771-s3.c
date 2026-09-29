#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

void push(Node** top_ref, char new_data) {
    if (top_ref == NULL) return;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    new_node->data = new_data;
    new_node->next = (*top_ref);
    (*top_ref) = new_node;
}

char pop(Node** top_ref) {
    if (top_ref == NULL || *top_ref == NULL) {
        return '\0';
    }
    
    Node* top = *top_ref;
    char res = top->data;
    *top_ref = top->next;
    free(top);
    return res;
}

bool isMatchingPair(char character1, char character2) {
    if (character1 == '(' && character2 == ')') return true;
    if (character1 == '{' && character2 == '}') return true;
    if (character1 == '[' && character2 == ']') return true;
    return false;
}

bool isBalanced(const char* exp) {
    if (exp == NULL) return false;
    
    Node* stack = NULL;
    int i = 0;
    
    while (exp[i] != '\0') {
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[') {
            push(&stack, exp[i]);
        }
        else if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            if (stack == NULL) {
                return false;
            }
            char poised = pop(&stack);
            if (!isMatchingPair(poised, exp[i])) {
                while (stack != NULL) {
                    pop(&stack);
                }
                return false;
            }
        }
        i++;
    }
    
    bool result = (stack == NULL);
    
    while (stack != NULL) {
        pop(&stack);
    }
    
    return result;
}

int main(void) {
    const char* exp1 = "{()}[]";
    const char* exp2 = "{([)}]";
    
    if (isBalanced(exp1)) {
        printf("Expression 1 is Balanced\n");
    } else {
        printf("Expression 1 is Not Balanced\n");
    }
    
    if (isBalanced(exp2)) {
        printf("Expression 2 is Balanced\n");
    } else {
        printf("Expression 2 is Not Balanced\n");
    }
    
    return EXIT_SUCCESS;
}