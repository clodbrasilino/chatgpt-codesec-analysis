#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->data = data;
    node->next = NULL;
    return node;
}

Node* zipLists(Node* list1, Node* list2) {
    Node* head = newNode(0);
    Node* current = head;
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
    /* Possible weaknesses found:
     *  leak of 'head' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return head->next;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* list1 = newNode(1);
    list1->next = newNode(3);
    list1->next->next = newNode(5);

    Node* list2 = newNode(2);
    list2->next = newNode(4);
    list2->next->next = newNode(6);

    Node* zippedList = zipLists(list1, list2);

    printList(zippedList);

    return 0;
}