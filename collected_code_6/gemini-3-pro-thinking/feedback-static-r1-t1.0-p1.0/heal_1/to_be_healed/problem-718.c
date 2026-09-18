#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!newNode) {
        return 0;
    }
    if (*head == NULL) {
        *head = newNode;
        return 1;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return 1;
}

Node* createAlternateList(Node* head) {
    Node* newList = NULL;
    Node* newTail = NULL;
    Node* current = head;

    while (current != NULL) {
        Node* newNode = createNode(current->data);
        if (!newNode) {
            freeList(newList);
            return NULL;
        }

        if (newList == NULL) {
            newList = newNode;
            newTail = newList;
        } else {
            newTail->next = newNode;
            newTail = newTail->next;
        }

        current = current->next;
        if (current != NULL) {
            current = current->next;
        }
    }

    return newList;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* originalList = NULL;
    Node* alternateList = NULL;

    for (int i = 1; i <= 10; ++i) {
        if (!appendNode(&originalList, i)) {
            freeList(originalList);
            return EXIT_FAILURE;
        }
    }

    printList(originalList);

    alternateList = createAlternateList(originalList);
    if (alternateList == NULL && originalList != NULL) {
        freeList(originalList);
        return EXIT_FAILURE;
    }

    printList(alternateList);

    freeList(originalList);
    freeList(alternateList);

    return EXIT_SUCCESS;
}