#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->data = data;
    node->next = NULL;
    return node;
}

void push(Node** head, int data) {
    Node* node = newNode(data);
    node->next = *head;
    *head = node;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void findSingleOccurrence(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        Node* innerTemp = head;
        int count = 0;
        while (innerTemp != NULL) {
            if (innerTemp->data == temp->data) {
                count++;
            }
            innerTemp = innerTemp->next;
        }
        if (count == 1) {
            printf("%d ", temp->data);
        }
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    push(&head, 5);
    push(&head, 3);
    push(&head, 2);
    push(&head, 2);
    push(&head, 1);
    push(&head, 1);
    push(&head, 1);
    push(&head, 0);

    printf("Original List: ");
    printList(head);

    printf("Elements that occur singly: ");
    findSingleOccurrence(head);

    return 0;
}