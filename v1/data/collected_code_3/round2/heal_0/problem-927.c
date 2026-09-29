#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

int max(int a, int b) {
    return (a >= b)? a: b;
}

int height(struct Node* node) {
    if (node == NULL)
        return 0;
    else
        return 1 + max(height(node->left), height(node->right));
}

int main() {
    struct Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    
    printf("Height of tree is %d", height(root));
  
    return 0;
}