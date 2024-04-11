#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int max(int a, int b) {
    return (a >= b)? a: b;
}

int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

int isBalanced(struct Node *root) {
    int lh;
    int rh;

    if(root == NULL)
        return 1;

    lh = height(root->left);
    rh = height(root->right);

    if( abs(lh-rh) <= 1 && isBalanced(root->left) && isBalanced(root->right))
        return 1;

    return 0;
}

int main() {
    struct Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    if(isBalanced(root))
        printf("Tree is balanced");
    else
        printf("Tree is not balanced");

    return 0;
}