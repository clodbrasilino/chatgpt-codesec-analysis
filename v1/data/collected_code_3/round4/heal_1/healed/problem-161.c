#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void push(Node** head_ref, int new_data) {
    Node* new_node = newNode(new_data);
    if(new_node == NULL) {
        return;
    }
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void removeElements(Node** list1, Node* list2) {
    Node* temp = *list1;
    Node* prev = NULL;

    while (temp != NULL && list2 != NULL) {
        if (temp->data == list2->data) {
            if (prev == NULL) {
                *list1 = temp->next;
            } else {
                prev->next = temp->next;
            }
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
            list2 = list2->next;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;

    push(&list1, 7);
    push(&list1, 6);
    push(&list1, 5);
    push(&list1, 4);
    push(&list1, 3);
    push(&list1, 2);
    push(&list1, 1);

    push(&list2, 3);
    push(&list2, 2);
    push(&list2, 1);

    printf("List 1 before removal: ");
    printList(list1);

    printf("List 2: ");
    printList(list2);

    removeElements(&list1, list2);

    printf("List 1 after removal: ");
    printList(list1);

    return 0;
}
