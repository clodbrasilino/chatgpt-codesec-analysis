#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void splitList(struct Node* head, int k, struct Node** first_head, struct Node** second_head) {
    if (head == NULL) {
        *first_head = NULL;
        *second_head = NULL;
        return;
    }

    if (k <= 0) {
        *first_head = NULL;
        *second_head = head;
        return;
    }

    struct Node* current = head;
    int count = 1;

    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        *first_head = head;
        *second_head = NULL;
        return;
    }

    *first_head = head;
    *second_head = current->next;
    current->next = NULL;
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
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
    if (head == NULL) return 1;
    
    head->next = createNode(2);
    if (head->next == NULL) { freeList(head); return 1; }
    
    head->next->next = createNode(3);
    if (head->next->next == NULL) { freeList(head); return 1; }
    
    head->next->next->next = createNode(4);
    if (head->next->next->next == NULL) { freeList(head); return 1; }
    
    head->next->next->next->next = createNode(5);
    if (head->next->next->next->next == NULL) { freeList(head); return 1; }

    struct Node* first_head = NULL;
    struct Node* second_head = NULL;
    int k = 3;

    splitList(head, k, &first_head, &second_head);

    printList(first_head);
    printList(second_head);

    freeList(first_head);
    freeList(second_head);

    return 0;
}