#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

int max(int a, int b) {
    return (a >= b) ? a : b;
}

int height(struct Node* node) {
    if (node == NULL)
        return 0;
    else
        return 1 + max(height(node->left), height(node->right));
}

int main() {
    struct Node *root = newNode(1);
    if (root == NULL) {
        return 1;
    }

    root->left = newNode(2);
    if (root->left == NULL) {
        free(root);
        return 1;
    }

    root->right = newNode(3);
    if(root->right == NULL){
        free(root->left);
        free(root);
        return 1;
    }

    root->left->left = newNode(4);
    if(root->left->left == NULL){
        free(root->right);
        free(root->left);
        free(root);
        return 1;
    }

    root->left->right = newNode(5);
    if(root->left->right == NULL){
        free(root->left->left);
        free(root->right);
        free(root->left);
        free(root);
        return 1;
    }

    printf("Height of tree is %d", height(root));

    // don't forget to free the memory
    free(root->left->right);
    free(root->left->left);
    free(root->right);
    free(root->left);
    free(root);

    return 0;
}