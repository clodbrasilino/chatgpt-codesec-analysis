#include <stdio.h>
#include <stdlib.h>

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

Node *merge_sorted_lists(Node *list1, Node *list2) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    return dummy.next;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;
    Node *merged = NULL;

    append_node(&list1, 1);
    append_node(&list1, 3);
    append_node(&list1, 5);
    append_node(&list1, 7);

    append_node(&list2, 2);
    append_node(&list2, 4);
    append_node(&list2, 6);
    append_node(&list2, 8);

    printf("List 1: ");
    print_list(list1);
    printf("List 2: ");
    print_list(list2);

    merged = merge_sorted_lists(list1, list2);

    printf("Merged: ");
    print_list(merged);

    free_list(merged);

    return 0;
}