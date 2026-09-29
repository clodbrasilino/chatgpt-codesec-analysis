#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void append(Node **head, int value) {
    Node *newNode = create_node(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

Node* divide_lists(Node *list1, Node *list2, Node **remainder) {
    *remainder = list1;
    Node *result = NULL;
    Node *prev = NULL;

    while (*remainder != NULL && list2 != NULL) {
        if ((*remainder)->value >= list2->value) {
            Node *temp = *remainder;
            *remainder = (*remainder)->next;
            temp->next = result;
            result = temp;
            list2 = list2->next;
        } else {
            prev = *remainder;
            *remainder = (*remainder)->next;
        }
    }

    if (prev != NULL) {
        prev->next = *remainder;
    }

    return result;
}

int main() {
    Node *list1 = NULL;
    Node *list2 = NULL;
    Node *remainder = NULL;

    append(&list1, 10);
    append(&list1, 20);
    append(&list1, 30);
    append(&list1, 40);

    append(&list2, 5);
    append(&list2, 15);
    append(&list2, 25);

    Node *result = divide_lists(list1, list2, &remainder);

    for (Node *current = result; current != NULL; current = current->next) {
        printf("%d ", current->value);
    }
    printf("\n");

    for (Node *current = remainder; current != NULL; current = current->next) {
        printf("%d ", current->value);
    }
    printf("\n");

    for (Node *current = list2, *next; current != NULL; current = next) {
        next = current->next;
        free(current);
    }

    for (Node *current = list1, *next; current != NULL; current = next) {
        next = current->next;
        free(current);
    }

    for (Node *current = result, *next; current != NULL; current = next) {
        next = current->next;
        free(current);
    }

    return 0;
}