#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    bool is_tuple;
    int value;
    struct Node *child;
    struct Node *next;
} Node;

Node *create_value(int val) {
    Node *n = malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_tuple = false;
    n->value = val;
    n->child = NULL;
    n->next = NULL;
    return n;
}

Node *create_tuple(Node *first_child) {
    Node *n = malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_tuple = true;
    n->value = 0;
    n->child = first_child;
    n->next = NULL;
    return n;
}

int *extract_evens(Node *root, int *count) {
    int capacity = 16;
    int *evens = malloc(capacity * sizeof(int));
    if (!evens) {
        *count = 0;
        return NULL;
    }
    *count = 0;

    Node *stack[1024];
    int top = 0;
    
    if (root) {
        if (top < 1024) stack[top++] = root;
    }

    while (top > 0) {
        Node *curr = stack[--top];
        while (curr) {
            if (curr->is_tuple) {
                if (curr->child && top < 1024) {
                    stack[top++] = curr->child;
                }
            } else {
                if (curr->value % 2 == 0) {
                    if (*count >= capacity) {
                        capacity *= 2;
                        int *temp = realloc(evens, capacity * sizeof(int));
                        if (!temp) {
                            free(evens);
                                            *count = 0;
                                            return NULL;
                        }
                        evens = temp;
                    }
                    evens[(*count)++] = curr->value;
                }
            }
            curr = curr->next;
        }
    }

    return evens;
}

void free_tree(Node *root) {
    if (!root) return;
    Node *stack[1024];
    int top = 0;
    if (top < 1024) stack[top++] = root;

    while (top > 0) {
        Node *curr = stack[--top];
        while (curr) {
            if (curr->child && top < 1024) {
                stack[top++] = curr->child;
            }
            Node *next = curr->next;
            free(curr);
            curr = next;
        }
    }
}

int main(void) {
    Node *inner_tuple = create_tuple(create_value(5));
    inner_tuple->child->next = create_value(8);
    
    Node *root = create_tuple(create_value(1));
    root->child->next = create_tuple(create_value(2));
    root->child->next->child = create_value(3);
    root->child->next->child->next = create_value(4);
    root->child->next->next = create_value(6);
    root->child->next->next->next = inner_tuple;

    int count = 0;
    int *evens = extract_evens(root, &count);

    for (int i = 0; i < count; i++) {
        printf("%d ", evens[i]);
    }
    printf("\n");

    free(evens);
    free_tree(root);

    return 0;
}