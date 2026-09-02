#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

void addNode(List *list, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = list->head;
    list->head = newNode;
}

int contains(Node *head, int value) {
    while (head != NULL) {
        if (head->value == value) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void removeDuplicates(List *list) {
    Node *current = list->head;
    while (current != NULL && current->next != NULL) {
        Node *runner = current;
        while (runner->next != NULL) {
            if (current->value == runner->next->value) {
                Node *temp = runner->next;
                runner->next = runner->next->next;
                free(temp);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
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
    list->head = NULL;
}

int main() {
    List list = {NULL};
    addNode(&list, 3);
    addNode(&list, 2);
    addNode(&list, 1);
    addNode(&list, 2);
    addNode(&list, 3);
    addNode(&list, 4);

    printf("Original list: ");
    printList(&list);

    removeDuplicates(&list);

    printf("List after removing duplicates: ");
    printList(&list);

    freeList(&list);
    return 0;
}