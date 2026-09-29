#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void splitList(struct Node* head, int position, struct Node** firstList, struct Node** secondList) {
    struct Node* current = head;
    int count = 1;

    if (head == NULL)
        return;

    while (count < position && current != NULL) {
        current = current->next;
        count++;
    }

    if (current == NULL)
        return;

    *firstList = head;
    *secondList = current->next;
    current->next = NULL;
}

void push(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = (*head);
    (*head) = newNode;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* head = NULL;
    struct Node* firstList = NULL;
    struct Node* secondList = NULL;

    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);

    printf("Original List: ");
    printList(head);

    splitList(head, 3, &firstList, &secondList);

    printf("\nFirst part of the list: ");
    printList(firstList);

    printf("\nSecond part of the list: ");
    printList(secondList);

    return 0;
}