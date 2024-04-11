#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

struct List {
    struct Node* head;
};

int getFirstElement(struct List* list) {
    if (list->head != NULL) {
        return list->head->data;
    }
    return -1;
}

int main() {
    struct Node node1, node2, node3;
    struct List list;

    node1.data = 10;
    node2.data = 20;
    node3.data = 30;

    node1.next = &node2;
    node2.next = &node3;
    node3.next = NULL;

    list.head = &node1;

    printf("First element of the list is: %d\n", getFirstElement(&list));

    return 0;
}