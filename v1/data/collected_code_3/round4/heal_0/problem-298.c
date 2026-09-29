#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
}

struct Node* findNestedElements(struct Node* list1, struct Node* list2) {
    struct Node* result = NULL;
    struct Node* temp;

    for (temp = list1; temp != NULL; temp = temp->next) {
        struct Node* temp2;
        for (temp2 = list2; temp2 != NULL; temp2 = temp2->next) {
            if (temp->data == temp2->data) {
                push(&result, temp->data);
            }
        }
    }
    return result;
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    struct Node* intersect = NULL;

    push(&list1, 20);
    push(&list1, 4);
    push(&list1, 15);
    push(&list1, 10);

    push(&list2, 10);
    push(&list2, 2);
    push(&list2, 4);
    push(&list2, 8);

    intersect = findNestedElements(list1, list2);

    printf("Intersected Linked List is: ");
    printList(intersect);

    return 0;
}