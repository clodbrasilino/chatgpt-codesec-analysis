#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* removeOddNumbers(Node *head) {
    Node *current = head;
    Node *prev = NULL;
    
    while (current != NULL) {
        if (current->data % 2 != 0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            Node *temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return head;
}

void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = (Node *)malloc(sizeof(Node));
    Node *second = (Node *)malloc(sizeof(Node));
    Node *third = (Node *)malloc(sizeof(Node));
    Node *fourth = (Node *)malloc(sizeof(Node));
    
    head->data = 1;
    head->next = second;
    
    second->data = 2;
    second->next = third;
    
    third->data = 3;
    third->next = fourth;
    
    fourth->data = 4;
    fourth->next = NULL;
    
    printf("Original List: ");
    printList(head);
    
    head = removeOddNumbers(head);
    
    printf("List after removing odd numbers: ");
    printList(head);
    
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}