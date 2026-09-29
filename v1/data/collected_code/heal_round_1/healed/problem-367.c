#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    
    if(node == NULL){
        return NULL;
    }
    
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int height(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int isBalanced(struct Node* root) {
    if (root == NULL) {
        return 1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return 1;
    }
    return 0;
}

int main() {
    struct Node* root = newNode(1);
    
    if(root == NULL){
        return 1;
    }
    
    root->left = newNode(2);
    root->right = newNode(3);
    
    if(root->left == NULL || root->right == NULL){
        return 1;
    }
    
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    
    if(root->left->left == NULL || root->left->right == NULL){
        return 1;
    }
    
    if (isBalanced(root)) {
        printf("The binary tree is balanced.\n");
    }
    else {
        printf("The binary tree is not balanced.\n");
    }
    return 0;
}