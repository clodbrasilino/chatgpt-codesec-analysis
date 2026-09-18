#include <stdio.h>
#include <stdlib.h>

// Node definition
struct Node {
    int data;
    struct Node *next;
};

// Function to create a node
struct Node* createNode(int data) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));

    if (node == NULL) {
        printf("Failed to allocate memory for node.\n");
        exit(0);
    }

    node->data = data;
    node->next = NULL;

    return node;
}

// Function to copy list from a singleton tuple
struct Node* copyList(struct Node *node) {
    if (node == NULL) {
        printf("Source node is NULL.\n");
        exit(0);
    }

    struct Node* temp = createNode(node->data);
    struct Node* head = temp;

    node = node->next;

    while (node != NULL) {
        temp->next = createNode(node->data);
        temp = temp->next;
        node = node->next;
    }

    return head;
}

// Main function
int main(void) {
    struct Node *node = createNode(1);
    node->next = createNode(2);
    node->next->next = createNode(3);

    /* Possible weaknesses found:
     *  Potential leak of memory pointed to by 'node' [unix.Malloc]
     */
    struct Node *copy = copyList(node);

    /* Possible weaknesses found:
     *  Potential leak of memory pointed to by 'copy' [unix.Malloc]
     */
    while(copy != NULL) {
        printf("%d ", copy->data);
        copy = copy->next;
    }

    return 0;
}