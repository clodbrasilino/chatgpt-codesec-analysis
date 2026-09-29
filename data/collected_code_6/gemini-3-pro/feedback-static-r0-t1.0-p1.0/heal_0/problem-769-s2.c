#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int isPresent(Node* head, int data) {
    Node* temp = head;
    while (temp) {
        if (temp->data == data) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

Node* getDifference(Node* list1, Node* list2) {
    Node* diffList = NULL;
    Node* temp = list1;

    while (temp) {
        if (!isPresent(list2, temp->data)) {
            appendNode(&diffList, temp->data);
        }
        temp = temp->next;
    }

    return diffList;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* diffList = NULL;

    appendNode(&list1, 1);
    appendNode(&list1, 2);
    appendNode(&list1, 3);
    appendNode(&list1, 4);

    appendNode(&list2, 3);
    appendNode(&list2, 4);
    appendNode(&list2, 5);
    appendNode(&list2, 6);

    diffList = getDifference(list1, list2);

    printList(diffList);

    freeList(list1);
    freeList(list2);
    freeList(diffList);

    return 0;
}