#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList(Node* node) {
    List* newList = (List*)malloc(sizeof(List));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newList' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newList->head = node;
    newList->next = NULL;
    return newList;
}

void addNode(List* list, int data) {
    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = createNode(data);
}

void addList(List** list, Node* node) {
    List* newList = createList(node);
    newList->next = *list;
    *list = newList;
}

void removeEmptyLists(List** list) {
    List* current = *list;
    List* prev = NULL;
    while (current != NULL) {
        if (current->head == NULL) {
            if (prev == NULL) {
                *list = current->next;
            } else {
                prev->next = current->next;
            }
            List* temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

int main() {
    List* list = createList(createNode(1));
    addNode(list, 2);
    addNode(list, 3);
    addList(&list, NULL);
    addList(&list, createNode(4));
    removeEmptyLists(&list);
    return 0;
}