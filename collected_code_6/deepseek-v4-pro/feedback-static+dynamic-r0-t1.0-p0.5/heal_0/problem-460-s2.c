#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Sublist {
    Node* head;
    struct Sublist* next;
} Sublist;

int* getFirstElements(Sublist* sublists, int* count) {
    if (sublists == NULL || count == NULL) {
        return NULL;
    }

    int size = 0;
    Sublist* current = sublists;
    while (current != NULL) {
        size++;
        current = current->next;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    current = sublists;
    int index = 0;
    while (current != NULL) {
        if (current->head != NULL) {
            result[index] = current->head->data;
        } else {
            free(result);
            return NULL;
        }
        index++;
        current = current->next;
    }

    *count = size;
    return result;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Sublist* createSublist(Node* head) {
    Sublist* newSublist = (Sublist*)malloc(sizeof(Sublist));
    if (newSublist == NULL) {
        return NULL;
    }
    newSublist->head = head;
    newSublist->next = NULL;
    return newSublist;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void freeSublists(Sublist* sublists) {
    Sublist* current = sublists;
    while (current != NULL) {
        Sublist* temp = current;
        freeList(current->head);
        current = current->next;
        free(temp);
    }
}

int main() {
    Node* list1 = createNode(10);
    list1->next = createNode(20);
    list1->next->next = createNode(30);

    Node* list2 = createNode(40);
    list2->next = createNode(50);

    Node* list3 = createNode(60);

    Sublist* sublists = createSublist(list1);
    sublists->next = createSublist(list2);
    sublists->next->next = createSublist(list3);

    int count = 0;
    int* firstElements = getFirstElements(sublists, &count);

    if (firstElements != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%d ", firstElements[i]);
        }
        printf("\n");
        free(firstElements);
    }

    freeSublists(sublists);

    return 0;
}