#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node* node) {
    if (node == NULL)
        return 0;
    else {
        int left_height = height(node->left);
        int right_height = height(node->right);
        return max(left_height, right_height) + 1;
    }
}

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    if(node == NULL) {
        return NULL;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {
    struct Node* root = newNode(1);
    if(root == NULL) {
        return -1;
    }

    root->left = newNode(2);
    if(root->left == NULL) {
        return -1;
    }

    root->right = newNode(3);
    if(root->right == NULL) {
        return -1;
    }

    root->left->left = newNode(4);
    if(root->left->left == NULL) {
        return -1;
    }

    root->left->right = newNode(5);
    if(root->left->right == NULL) {
        return -1;
    }
    
    int tree_height = height(root);
    
    printf("Height of the binary tree is: %d\n", tree_height);
    
    return 0;
}