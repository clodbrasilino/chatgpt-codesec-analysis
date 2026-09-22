#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* createNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void append(Node **head, int value) {
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

int listContains(Node *head, int value) {
    Node *current = head;
    while (current) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void subtractLists(Node **list1, Node *list2) {
    Node *current1 = *list1;
    Node *prev = NULL;

    while (current1) {
        if (listContains(list2, current1->value)) {
            Node *toDelete = current1;
            if (prev) {
                prev->next = current1->next;
            } else {
                *list1 = current1->next;
            }
            free(toDelete);
            current1 = prev ? prev->next : *list1;
        } else {
            prev = current1;
            current1 = current1->next;
        }
    }
}

void printList(Node *head) {
    Node *current = head;
    while (current) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Node *list1 = NULL;
    Node *list2 = NULL;

    append(&list1, 1);
    append(&list1, 2);
    append(&list1, 3);
    append(&list1, 4);

    append(&list2, 2);
    append(&list2, 4);

    printf("List 1 before subtraction: ");
    printList(list1);
    printf("List 2: ");
    printList(list2);

    subtractLists(&list1, list2);

    printf("List 1 after subtraction: ");
    printList(list1);

    // Free remaining nodes in list1
    while (list1) {
        Node *toDelete = list1;
        list1 = list1->next;
        free(toDelete);
    }

    // Free remaining nodes in list2
    while (list2) {
        Node *toDelete = list2;
        list2 = list2->next;
        free(toDelete);
    }

    return 0;
}