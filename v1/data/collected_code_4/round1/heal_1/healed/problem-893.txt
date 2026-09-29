#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node *) malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void printLastInSubList(struct Node *node) {
    if (node == NULL) {
        return;
    }

    while (node->next != NULL) {
        node = node->next;
    }

    printf("%d", node->data);
}

int main() {
    struct Node *root = newNode(1);
    if (root == NULL) {
        return 1; 
    }
    root->next = newNode(2);
    if (root->next == NULL) {
        free(root);
        return 1; 
    }
    root->next->next = newNode(3);
    if (root->next->next == NULL) {
        free(root->next);
        free(root);
        return 1; 
    }

    printLastInSubList(root);

    free(root->next->next);
    free(root->next);
    free(root);

    return 0;
}