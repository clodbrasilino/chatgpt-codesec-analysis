#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node **head, int data) {
    Node *newNode = createNode(data);
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

int listLength(Node *head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

Node* interleaveLists(Node *list1, Node *list2) {
    if (list1 == NULL || list2 == NULL) {
        return list1 ? list1 : list2;
    }

    Node *result = NULL;
    Node *tail = NULL;

    while (list1 && list2) {
        if (result == NULL) {
            result = tail = createNode(list1->data);
        } else {
            tail->next = createNode(list1->data);
            tail = tail->next;
        }
        list1 = list1->next;

        tail->next = createNode(list2->data);
        tail = tail->next;
        list2 = list2->next;
    }

    if (list1) {
        tail->next = list1;
    } else if (list2) {
        tail->next = list2;
    }

    return result;
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
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

    Node *interleaved = interleaveLists(list1, list2);
    printList(interleaved);

    return 0;
}