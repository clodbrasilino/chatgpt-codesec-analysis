#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertBeforeEach(struct Node** head_ref, int element) {
    if (head_ref == NULL || *head_ref == NULL) {
        return;
    }

    struct Node* current = *head_ref;
    struct Node* prev = NULL;

    while (current != NULL) {
        struct Node* newNode = createNode(element);
        
        if (prev == NULL) {
            newNode->next = *head_ref;
            *head_ref = newNode;
        } else {
            newNode->next = current;
            prev->next = newNode;
        }
        
        prev = current;
        current = current->next;
    }
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);

    insertBeforeEach(&head, 0);

    printList(head);

    freeList(head);

    return 0;
}