#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        perror("Unable to allocate memory for new node.");
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node* zipLists(Node* list1, Node* list2) {
    Node* head = newNode(0);
    Node* current = head;
    if (!head) {
        perror("Unable to allocate memory for head node.");
        return NULL;
    }
    while (list1 != NULL || list2 != NULL) {
        if (list1 != NULL) {
            current->next = list1;
            current = current->next;
            list1 = list1->next;
        }
        if (list2 != NULL) {
            current->next = list2;
            current = current->next;
            list2 = list2->next;
        }
    }
    current = head->next;
    free(head);
    return current;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void freeList(Node* node) {
    Node* tmp;
    while (node != NULL) {
        tmp = node;
        node = node->next;
        free(tmp);
    }
}

int main() {
    Node* list1 = newNode(1);
    list1->next = newNode(3);
    list1->next->next = newNode(5);

    Node* list2 = newNode(2);
    list2->next = newNode(4);
    list2->next->next = newNode(6);

    Node* result = zipLists(list1, list2);

    printList(result);

    // Freeing up the lists.
    freeList(list1);
    freeList(list2);
    freeList(result);

    return 0;
}