#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data)
{
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));

    if(node != NULL)
    {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
    }
    
    return node;
}

int maxDepth(struct Node* node)
{
    if (node == NULL) 
        return 0;
    else
    {
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);

        if (lDepth > rDepth) 
            return lDepth + 1;
        else 
            return rDepth + 1;
    }
}   
  
int main()
{
    struct Node *root = newNode(1);
  
    if (root != NULL)
    {
        root->left = newNode(2);
        root->right = newNode(3);

        if (root->left != NULL)
        {
            root->left->left = newNode(4);
            root->left->right = newNode(5);
        }
        
        printf("Height of tree is %d", maxDepth(root));
    }
  
    return 0;
}