#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node **head, int value) {
    Node *newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

Node* mergeSortedLists(Node *list1, Node *list2) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->value <= list2->value) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    return dummy.next;
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
    Node *list2 = NULL;

    appendNode(&list1, 1);
    appendNode(&list1, 3);
    appendNode(&list1, 5);

    appendNode(&list2, 2);
    appendNode(&list2, 4);
    appendNode(&list2, 6);

    Node *mergedList = mergeSortedLists(list1, list2);

    printList(mergedList);

    return 0;
}