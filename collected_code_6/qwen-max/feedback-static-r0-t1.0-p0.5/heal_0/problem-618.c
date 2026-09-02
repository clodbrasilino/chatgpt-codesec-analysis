#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void append(Node **head, int value) {
    Node *new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

Node* divide_lists(Node *list1, Node *list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }

    Node *result = NULL;
    Node *current1 = list1;
    Node *current2 = list2;

    while (current1 != NULL && current2 != NULL) {
        if (current1->value % current2->value == 0) {
            append(&result, current1->value / current2->value);
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    return result;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node *list1 = NULL;
    Node *list2 = NULL;

    append(&list1, 4);
    append(&list1, 8);
    append(&list1, 12);

    append(&list2, 2);
    append(&list2, 4);
    append(&list2, 6);

    Node *result = divide_lists(list1, list2);

    print_list(result);

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}