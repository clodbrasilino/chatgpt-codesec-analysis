#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

bool has_common_element(Node *list1, Node *list2) {
    Node *current1 = list1;
    while (current1 != NULL) {
        Node *current2 = list2;
        while (current2 != NULL) {
            if (current1->data == current2->data) {
                return true;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    return false;
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;

    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 3);

    append_node(&list2, 4);
    append_node(&list2, 5);
    append_node(&list2, 3);

    if (has_common_element(list1, list2)) {
        printf("Lists have a common element\n");
    } else {
        printf("Lists do not have a common element\n");
    }

    free_list(list1);
    free_list(list2);

    return 0;
}