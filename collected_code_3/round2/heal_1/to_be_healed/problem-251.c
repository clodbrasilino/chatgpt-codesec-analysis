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

Node* insertBeforeEveryElement(Node* head, int data) {
    Node* current = head;
    Node* prev = NULL;
    while (current != NULL) {
        Node* node = newNode(data);
        if (prev == NULL) {
            node->next = head;
            head = node;
        } else {
            node->next = prev->next;
            prev->next = node;
        }
        prev = current;
        current = current->next;
    }
    return head;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);
    head->next->next->next->next = newNode(5);

    printf("Original List: ");
    printList(head);

    head = insertBeforeEveryElement(head, 0);

    printf("Modified List: ");
    printList(head);

    return 0;
}