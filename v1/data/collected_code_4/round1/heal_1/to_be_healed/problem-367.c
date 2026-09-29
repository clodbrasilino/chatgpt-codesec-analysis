#include <stdio.h> 
#include <stdlib.h> 

typedef struct node { 
    int data; 
    struct node* left; 
    struct node* right; 
} Node; 

int max(int a, int b);   
int height(Node* node);  
int isBalanced(Node* root); 

Node* createNode(int data) {
    Node* node = (Node*) malloc(sizeof(Node)); 
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->data = data; 
    node->left = NULL; 
    node->right = NULL; 
    return(node); 
} 

int max(int a, int b) { 
    return (a >= b)? a: b; 
} 

int height(Node* node) { 
    if (node == NULL) 
        return 0; 
    return 1 + max(height(node->left), height(node->right)); 
} 

int isBalanced(Node *root) { 
    int left; 
    int right; 

    if (root == NULL) 
        return 1; 

    left = height(root->left); 
    right = height(root->right); 

    if (abs(left - right) <= 1 && isBalanced(root->left) && isBalanced(root->right)) 
        return 1; 

    return 0; 
} 

int main() { 
    Node* root = createNode(1); 
    root->left = createNode(2); 
    root->right = createNode(3); 
    root->left->left = createNode(4); 
    root->left->right = createNode(5); 
    root->right->left = createNode(6); 
    root->left->left->left = createNode(7); 

    if(isBalanced(root)) 
        printf("Tree is balanced"); 
    else
        printf("Tree is not balanced"); 

    return 0; 
} 