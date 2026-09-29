#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int* data;
    int size;
    struct Node* next;
} Node;

Node* createNode(int* list, int size) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = list;
    newNode->size = size;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        if (temp->data != NULL) {
            free(temp->data);
        }
        head = head->next;
        free(temp);
    }
}

Node* removeEmptyLists(Node* head) {
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->size == 0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            Node* toDelete = current;
            current = current->next;
            free(toDelete->data);
            free(toDelete);
        } else {
            prev = current;
            current = current->next;
        }
    }

    return head;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {};
    int list3[] = {4, 5};

    Node* head = createNode(list1, 3);
    head->next = createNode(list2, 0);
    head->next->next = createNode(list3, 2);

    head = removeEmptyLists(head);

    Node* current = head;
    while (current != NULL) {
        for (int i = 0; i < current->size; ++i) {
            printf("%d ", current->data[i]);
        }
        printf("\n");
        current = current->next;
    }

    freeList(head);
    return 0;
}