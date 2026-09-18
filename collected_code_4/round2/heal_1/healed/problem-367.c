#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int val;
    struct node* left;
    struct node* right;
} Node;

int max(int a, int b) {
    return (a >= b) ? a : b;
}

int height(Node* root) {
    if (root == NULL) {
        return 0;
    }
    
    return 1 + max(height(root->left), height(root->right));
}

int isBalanced(Node* root) {
    if (root == NULL) {
        return 1;
    }
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    if (abs(leftHeight-rightHeight) <= 1 && 
        isBalanced(root->left) &&
        isBalanced(root->right)) {
        return 1;
    }
    
    return 0;
}

Node* newNode(int val) {
    Node* node = (Node*) malloc(sizeof(Node));
    
    if (node == NULL) {
        return NULL;
    }
    
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

int main() {
    Node* root = newNode(1);
    if (root == NULL) return 1;
    
    root->left = newNode(2);
    if (root->left == NULL) return 1;
    
    root->right = newNode(3);
    if (root->right == NULL) return 1;
    
    root->left->left = newNode(4);
    if (root->left->left == NULL) return 1;
    
    root->left->right = newNode(5);
    if (root->left->right == NULL) return 1;
    
    if(isBalanced(root)) {
        printf("Tree is balanced");
    } else {
        printf("Tree is not balanced");
    }
    
    return 0;
}