#include <stdio.h>

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct Dict {
    int key;
    struct Dict* child;
    struct Dict* next;
} Dict;

Dict* createDict(int key) {
    Dict* newDict = (Dict*)malloc(sizeof(Dict));
    newDict->key = key;
    newDict->child = NULL;
    newDict->next = NULL;
    return newDict;
}

void insertDict(Dict** root, Node* list) {
    if (!list) { // base case
        return;
    }
    
    if (!(*root)) { // if root is empty, create a new dictionary
        (*root) = createDict(list->key);
    } else if ((*root)->key == list->key) { // if root key matches list key, insert the value as child
        Dict* newChild = createDict(list->value);
        newChild->next = (*root)->child;
        (*root)->child = newChild;
    } else {
        insertDict(&(*root)->next, list); // recursive call on next dictionary
    }
    
    insertDict(&(*root)->child, list->next); // recursive call on child dictionary
}

void printDict(Dict* root, int depth) {
    if (!root) { // base case
        return;
    }
    
    for (int i = 0; i < depth; i++) {
        printf("\t");
    }
    
    printf("%d\n", root->key);
    printDict(root->child, depth + 1);
    printDict(root->next, depth);
}

int main() {
    Node* list1 = (Node*)malloc(sizeof(Node));
    list1->key = 1;
    list1->value = 10;
    list1->next = (Node*)malloc(sizeof(Node));
    list1->next->key = 2;
    list1->next->value = 20;
    list1->next->next = NULL;

    Node* list2 = (Node*)malloc(sizeof(Node));
    list2->key = 1;
    list2->value = 100;
    list2->next = (Node*)malloc(sizeof(Node));
    list2->next->key = 3;
    list2->next->value = 300;
    list2->next->next = NULL;

    Dict* root = NULL;
    insertDict(&root, list1);
    insertDict(&root, list2);

    printDict(root, 0);

    return 0;
}