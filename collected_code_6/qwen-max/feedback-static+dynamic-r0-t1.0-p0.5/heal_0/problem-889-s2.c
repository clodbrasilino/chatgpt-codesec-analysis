#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

void reverseList(List *list) {
    Node *prev = NULL;
    Node *current = list->head;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

void reverseLists(List **lists, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (lists[i] != NULL) {
            reverseList(lists[i]);
        }
    }
}

Node* createNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

List* createList() {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    return list;
}

void appendToList(List *list, int value) {
    Node *newNode = createNode(value);
    if (newNode == NULL) {
        return;
    }
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    List *list1 = createList();
    List *list2 = createList();
    List *list3 = createList();

    appendToList(list1, 1);
    appendToList(list1, 2);
    appendToList(list1, 3);

    appendToList(list2, 4);
    appendToList(list2, 5);

    appendToList(list3, 6);
    appendToList(list3, 7);
    appendToList(list3, 8);
    appendToList(list3, 9);

    List *lists[] = {list1, list2, list3};
    size_t count = sizeof(lists) / sizeof(lists[0]);

    printf("Before reversing:\n");
    for (size_t i = 0; i < count; ++i) {
        printList(lists[i]);
    }

    reverseLists(lists, count);

    printf("After reversing:\n");
    for (size_t i = 0; i < count; ++i) {
        printList(lists[i]);
    }

    for (size_t i = 0; i < count; ++i) {
        freeList(lists[i]);
    }

    return 0;
}