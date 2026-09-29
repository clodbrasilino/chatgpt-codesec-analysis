#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *key;
    struct node *child;
    struct node *next;
} Node;

Node* createNode(char *key) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    if (!newNode) {
        return NULL;
    }

    newNode->key = strdup(key);
    newNode->child = NULL;
    newNode->next = NULL;
    return newNode;
}

Node* convertListToDict(char **list, int size) {
    Node *root = createNode(list[0]);

    if (!root) {
        return NULL;
    }

    Node *temp = root;

    for(int i = 1; i < size; i++) {
        temp->child = createNode(list[i]);

        if (!temp->child) {
            return NULL;
        }

        temp = temp->child;
    }

    return root;
}

void printDict(Node *root) {
    while(root != NULL) {
        printf("%s ", root->key);
        if(root->child != NULL) {
            printf("-> ");
            printDict(root->child);
        }
        root = root->next;
    }
}

int main() {
    char *list1[] = {"A", "B", "C", "D"};
    char *list2[] = {"E", "F", "G", "H"};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);

    Node *dict1 = convertListToDict(list1, size1);
    Node *dict2 = convertListToDict(list2, size2);

    if (!dict1 || !dict2) {
        return -1;
    }

    dict1->next = dict2;
    printDict(dict1);

    return 0;
}