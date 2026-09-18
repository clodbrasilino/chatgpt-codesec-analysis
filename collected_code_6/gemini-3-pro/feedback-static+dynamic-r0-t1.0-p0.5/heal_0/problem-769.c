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
    if (!head) return;
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

void freeList(Node* head) {
    Node* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int contains(Node* head, int data) {
    Node* current = head;
    while (current) {
        if (current->data == data) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Node* getDifference(Node* list1, Node* list2) {
    Node* diffList = NULL;
    Node* current = list1;

    while (current) {
        if (!contains(list2, current->data) && !contains(diffList, current->data)) {
            appendNode(&diffList, current->data);
        }
        current = current->next;
    }

    return diffList;
}

void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
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
    appendNode(&list1, 5);

    appendNode(&list2, 3);
    appendNode(&list2, 4);
    appendNode(&list2, 6);

    diffList = getDifference(list1, list2);

    printList(diffList);

    freeList(list1);
    freeList(list2);
    freeList(diffList);

    return EXIT_SUCCESS;
}