#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** list, Node* node) {
    if (*list == NULL) {
        *list = node;
    } else {
        Node* temp = *list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

Node* divideLists(Node* list1, Node* list2) {
    Node* resultList = NULL;
    Node* current1 = list1;
    Node* current2 = list2;

    while (current1 != NULL && current2 != NULL) {
        int result = current1->data / current2->data;
        Node* newNode = createNode(result);
        appendNode(&resultList, newNode);

        current1 = current1->next;
        current2 = current2->next;
    }

    return resultList;
}

void printList(Node* list) {
    while (list != NULL) {
        printf("%d -> ", list->data);
        list = list->next;
    }
    printf("NULL\n");
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;

    for (int i = 3; i > 0; --i) {
        appendNode(&list1, createNode(i));
    }
    for (int i = 4; i > 0; --i) {
        appendNode(&list2, createNode(i));
    }

    printList(list1);
    printList(list2);

    Node* resultList = divideLists(list1, list2);
    printList(resultList);

    Node* temp;
    while (list1 != NULL) {
        temp = list1;
        list1 = list1->next;
        free(temp);
    }
    while (list2 != NULL) {
        temp = list2;
        list2 = list2->next;
        free(temp);
    }
    while (resultList != NULL) {
        temp = resultList;
        resultList = resultList->next;
        free(temp);
    }

    return 0;
}