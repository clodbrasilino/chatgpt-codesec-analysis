#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* removeNegatives(Node* head) {
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->data < 0) {
            Node* temp = current;
            current = current->next;

            if (prev == NULL) {
                head = current;
            } else {
                prev->next = current;
            }

            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }

    return head;
}

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    return node;
}

void printList(Node* head) {
    Node* current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    printf("\n");
}

int main() {
    Node* head = newNode(-10);

    if (head == NULL) {
        return 1;
    }

    head->next = newNode(20);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next = newNode(-30);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next = newNode(40);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next->next = newNode(-50);

    if (head->next == NULL || head->next->next == NULL ||
        head->next->next->next == NULL || head->next->next->next->next == NULL) {
        return 1;
    }

    printf("Original List: ");
    printList(head);

    head = removeNegatives(head);

    printf("List after removing negatives: ");
    printList(head);

    return 0;
}