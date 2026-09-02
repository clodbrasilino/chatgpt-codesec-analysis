#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* insert_before_each_element(Node *head, int insertData) {
    Node *current = head, *newNode, *temp;
    while (current != NULL) {
        newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) {
            return NULL;
        }
        newNode->data = insertData;
        if (current == head) {
            newNode->next = head;
            head = newNode;
        } else {
            temp = head;
            while (temp->next != current) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        current = current->next->next;
    }
    return head;
}

void print_list(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL, *second = NULL, *third = NULL;

    head = (Node *)malloc(sizeof(Node));
    second = (Node *)malloc(sizeof(Node));
    third = (Node *)malloc(sizeof(Node));

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    printf("Original list: ");
    print_list(head);

    head = insert_before_each_element(head, 0);

    printf("Modified list: ");
    print_list(head);

    // Free allocated memory
    Node *current = head;
    while (current != NULL) {
        Node *to_free = current;
        current = current->next;
        free(to_free);
    }

    return 0;
}