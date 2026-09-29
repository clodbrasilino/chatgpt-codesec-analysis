#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node **head, int value) {
    Node *newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void removeDuplicates(Node **head) {
    Node *current = *head;
    Node *prev = NULL;
    while (current != NULL && current->next != NULL) {
        if (current->value == current->next->value) {
            Node *temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            /* Possible weaknesses found:
             *  Variable 'prev' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'prev' is never read [deadcode.DeadStores]
             */
            prev = current;
            current = current->next;
        }
    }
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node *list1 = NULL;
    insertAtEnd(&list1, 1);
    insertAtEnd(&list1, 2);
    insertAtEnd(&list1, 2);
    insertAtEnd(&list1, 3);
    insertAtEnd(&list1, 4);
    insertAtEnd(&list1, 4);

    printf("Original list: ");
    printList(list1);

    removeDuplicates(&list1);

    printf("List after removing duplicates: ");
    printList(list1);

    while (list1 != NULL) {
        Node *temp = list1;
        list1 = list1->next;
        free(temp);
    }

    return 0;
}