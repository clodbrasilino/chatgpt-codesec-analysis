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
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

int main() {
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    
    if(isBalanced(root)) {
        printf("Tree is balanced");
    } else {
        printf("Tree is not balanced");
    }
    
    return 0;
}