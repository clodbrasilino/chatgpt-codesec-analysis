#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int data;
    struct List *next;
} List;

List* createNode(int data) {
    List *newNode = (List*)malloc(sizeof(List));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(List *head) {
    while (head != NULL) {
        List *temp = head;
        head = head->next;
        free(temp);
    }
}

List* alternateElements(List *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    List *newHead = createNode(head->data);
    List *current = newHead;
    head = head->next->next;

    while (head != NULL) {
        current->next = createNode(head->data);
        current = current->next;
        if (head->next == NULL) {
            break;
        }
        head = head->next->next;
    }

    return newHead;
}

int main() {
    List *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    List *newList = alternateElements(head);

    for (List *node = newList; node != NULL; node = node->next) {
        printf("%d ", node->data);
    }

    freeList(head);
    freeList(newList);

    return 0;
}