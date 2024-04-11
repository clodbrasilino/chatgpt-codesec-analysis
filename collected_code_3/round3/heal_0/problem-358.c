#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(Node** head_ref, int new_data) {
    Node* new_node = createNode(new_data);
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

Node* moduloDivision(Node* list1, Node* list2) {
    Node* result = NULL;
    while (list1 && list2) {
        if (list2->data == 0) {
            printf("Division by zero is not allowed\n");
            return NULL;
        }
        push(&result, list1->data % list2->data);
        list1 = list1->next;
        list2 = list2->next;
    }
    return result;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;

    push(&list1, 10);
    push(&list1, 20);
    push(&list1, 30);

    push(&list2, 2);
    push(&list2, 3);
    push(&list2, 5);

    result = moduloDivision(list1, list2);

    printList(result);

    return 0;
}