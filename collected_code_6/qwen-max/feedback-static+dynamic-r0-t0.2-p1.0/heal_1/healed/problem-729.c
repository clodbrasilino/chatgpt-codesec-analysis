#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
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

Node* addLists(Node *list1, Node *list2) {
    Node *result = NULL;
    Node *current1 = list1;
    Node *current2 = list2;
    int carry = 0;
    while (current1 != NULL || current2 != NULL || carry > 0) {
        int sum = (current1 ? current1->data : 0) + (current2 ? current2->data : 0) + carry;
        carry = sum / 10;
        appendNode(&result, sum % 10);
        if (current1) current1 = current1->next;
        if (current2) current2 = current2->next;
    }
    return result;
}

void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(Node *head) {
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

    appendNode(&list1, 7);
    appendNode(&list1, 1);
    appendNode(&list1, 6);

    appendNode(&list2, 5);
    appendNode(&list2, 9);
    appendNode(&list2, 2);

    Node *result = addLists(list1, list2);

    printList(result);

    freeList(list1);
    freeList(list2);
    freeList(result);

    return 0;
}