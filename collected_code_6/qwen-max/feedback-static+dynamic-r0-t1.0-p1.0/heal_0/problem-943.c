#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

Node* mergeSortedLists(Node* lst1, Node* lst2) {
    if (lst1 == NULL) {
        return lst2;
    }
    if (lst2 == NULL) {
        return lst1;
    }

    Node* result = NULL;
    if (lst1->data <= lst2->data) {
        result = lst1;
        result->next = mergeSortedLists(lst1->next, lst2);
    } else {
        result = lst2;
        result->next = mergeSortedLists(lst1, lst2->next);
    }
    return result;
}

int main() {
    Node* list1 = createNode(1);
    list1->next = createNode(3);
    list1->next->next = createNode(5);

    Node* list2 = createNode(2);
    list2->next = createNode(4);
    list2->next->next = createNode(6);

    Node* mergedList = mergeSortedLists(list1, list2);

    for (Node* temp = mergedList; temp != NULL; temp = temp->next) {
        printf("%d ", temp->data);
    }
    printf("\n");

    freeList(mergedList);
    return 0;
}