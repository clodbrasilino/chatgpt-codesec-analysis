#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* removeDuplicates(Node* head) {
    if (head == NULL) return NULL;
    
    Node* current = head;

    while (current->next != NULL) {
        if (current->data == current->next->data) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    return head;
}

Node* newNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->data = data;
    node->next = NULL;
    return node;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main() {
    Node* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(2);
    head->next->next->next = newNode(3);
    head->next->next->next->next = newNode(3);
    head->next->next->next->next->next = newNode(4);

    printf("List before removing duplicates \n");
    printList(head);

    head = removeDuplicates(head);

    printf("\nList after removing duplicates \n");
    printList(head);

    return 0;
}