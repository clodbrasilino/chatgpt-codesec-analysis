#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int listLength(Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

Node* interleaveLists(Node* list1, Node* list2) {
    if (list1 == NULL || list2 == NULL) return NULL;
    Node *result = NULL;
    Node *tail = NULL;
    Node *current1 = list1;
    Node *current2 = list2;

    while (current1 != NULL && current2 != NULL) {
        if (result == NULL) {
            result = createNode(current1->data);
            tail = result;
        } else {
            tail->next = createNode(current1->data);
            tail = tail->next;
        }
        current1 = current1->next;

        tail->next = createNode(current2->data);
        tail = tail->next;
        current2 = current2->next;
    }

    return result;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
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

    printList(list1);
    printList(list2);

    Node *interleavedList = interleaveLists(list1, list2);
    printList(interleavedList);

    freeList(list1);
    freeList(list2);
    freeList(interleavedList);

    return 0;
}