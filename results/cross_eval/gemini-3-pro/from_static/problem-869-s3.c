#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListOfLists {
    Node* head;
    struct ListOfLists* next;
} ListOfLists;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

ListOfLists* createListOfListsNode(Node* head) {
    ListOfLists* newNode = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->head = head;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

void freeListOfLists(ListOfLists* head) {
    while (head != NULL) {
        ListOfLists* tmp = head;
        head = head->next;
        freeList(tmp->head);
        free(tmp);
    }
}

void filterListOfLists(ListOfLists** headRef, int minSize, int maxSize) {
    if (!headRef || !*headRef) {
        return;
    }

    ListOfLists* current = *headRef;
    ListOfLists* prev = NULL;

    while (current != NULL) {
        int count = 0;
        Node* node = current->head;
        while (node != NULL) {
            count++;
            node = node->next;
        }

        if (count < minSize || count > maxSize) {
            ListOfLists* toDelete = current;
            if (prev == NULL) {
                *headRef = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            freeList(toDelete->head);
            free(toDelete);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}

void printListOfLists(ListOfLists* head) {
    while (head != NULL) {
        printf("[ ");
        printList(head->head);
        printf("]\n");
        head = head->next;
    }
}

int main() {
    Node* l1 = createNode(1);
    l1->next = createNode(2);
    l1->next->next = createNode(3);

    Node* l2 = createNode(4);
    l2->next = createNode(5);

    Node* l3 = createNode(6);
    l3->next = createNode(7);
    l3->next->next = createNode(8);
    l3->next->next->next = createNode(9);

    ListOfLists* lolList = createListOfListsNode(l1);
    lolList->next = createListOfListsNode(l2);
    lolList->next->next = createListOfListsNode(l3);

    filterListOfLists(&lolList, 2, 3);
    printListOfLists(lolList);

    freeListOfLists(lolList);
    lolList = NULL;

    return 0;
}