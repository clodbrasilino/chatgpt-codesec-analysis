#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node *createNewNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Exiting program.\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int countLists(struct Node **lists, int numLists) {
    int count = 0;
    for (int i = 0; i < numLists; i++) {
        if (lists[i] != NULL)
            count++;
    }
    return count;
}

int main() {
    int numLists = 5;
    struct Node *lists[numLists];
    
    for (int i = 0; i < numLists; i++) {
        lists[i] = NULL;
    }
    
    lists[0] = createNewNode(1);
    lists[0]->next = createNewNode(2);

    lists[2] = createNewNode(3);
    lists[2]->next = createNewNode(4);
    
    printf("Number of lists: %d", countLists(lists, numLists));
    
    return 0;
}