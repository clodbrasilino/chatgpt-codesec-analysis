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

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(node) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

List* newList(Node* node) {
    List* list = (List*)malloc(sizeof(List));
    if(list) {
        list->head = node;
        list->next = NULL;
    }
    return list;
}

void removeSublists(List** head, int min, int max) {
    List* prev = NULL;
    List* current = *head;

    while (current != NULL) {
        Node* node = current->head;
        while (node != NULL) {
            if (node->data < min || node->data > max) {
                if (prev == NULL) {
                    *head = current->next;
                } else {
                    prev->next = current->next;
                }
                List* temp = current;
                current = current->next;
                free(temp);
                break;
            }
            node = node->next;
        }
        if (node == NULL) {
            prev = current;
            current = current->next;
        }
    }
}

int main() {
    Node* node1 = newNode(5);
    /* Possible weaknesses found:
     *  dereference of NULL 'node1' [CWE-476] [-Wanalyzer-null-dereference]
     */
    node1->next = newNode(10);
    /* Possible weaknesses found:
     *  dereference of NULL '*node1.next' [CWE-476] [-Wanalyzer-null-dereference]
     */
    node1->next->next = newNode(15);

    Node* node2 = newNode(20);
    /* Possible weaknesses found:
     *  dereference of NULL 'node2' [CWE-476] [-Wanalyzer-null-dereference]
     */
    node2->next = newNode(25);
    /* Possible weaknesses found:
     *  dereference of NULL '*node2.next' [CWE-476] [-Wanalyzer-null-dereference]
     */
    node2->next->next = newNode(30);

    Node* node3 = newNode(35);
    node3->next = newNode(40);
    node3->next->next = newNode(45);

    List* list1 = newList(node1);
    List* list2 = newList(node2);
    List* list3 = newList(node3);

    list1->next = list2;
    list2->next = list3;

    removeSublists(&list1, 10, 40);

    return 0;
}