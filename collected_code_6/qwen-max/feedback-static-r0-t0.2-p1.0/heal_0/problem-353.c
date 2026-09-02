#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *down;
} List;

List* createNode(int value) {
    List *newNode = (List*)malloc(sizeof(List));
    newNode->head = (Node*)malloc(sizeof(Node));
    newNode->head->value = value;
    newNode->head->next = NULL;
    newNode->down = NULL;
    return newNode;
}

void append(List *list, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

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

List* addColumn(List *list, int value) {
    List *newColumn = createNode(value);
    newColumn->down = list;
    return newColumn;
}

List* removeColumn(List *list, int colIndex) {
    if (list == NULL || colIndex < 0) {
        return list;
    }

    if (colIndex == 0) {
        List *temp = list->down;
        free(list->head);
        free(list);
        return temp;
    }

    list->down = removeColumn(list->down, colIndex - 1);
    return list;
}

void printList(List *list) {
    while (list != NULL) {
        Node *current = list->head;
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("\n");
        list = list->down;
    }
}

int main() {
    List *list = createNode(1);
    append(list, 2);
    append(list, 3);

    list = addColumn(list, 4);
    append(list->down, 5);
    append(list->down, 6);

    list = addColumn(list, 7);
    append(list->down->down, 8);
    append(list->down->down, 9);

    printf("Original list:\n");
    printList(list);

    list = removeColumn(list, 1);

    printf("List after removing column 1:\n");
    printList(list);

    return 0;
}