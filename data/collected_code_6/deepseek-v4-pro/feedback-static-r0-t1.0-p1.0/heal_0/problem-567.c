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

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int is_sorted(Node *head) {
    if (head == NULL || head->next == NULL) {
        return 1;
    }
    Node *current = head;
    int ascending = 1;
    int descending = 1;
    while (current->next != NULL) {
        if (current->data > current->next->data) {
            ascending = 0;
        }
        if (current->data < current->next->data) {
            descending = 0;
        }
        if (!ascending && !descending) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

int main(void) {
    Node *list = NULL;
    append_node(&list, 10);
    append_node(&list, 20);
    append_node(&list, 30);
    append_node(&list, 40);
    append_node(&list, 50);
    
    if (is_sorted(list)) {
        printf("The list is sorted.\n");
    } else {
        printf("The list is not sorted.\n");
    }
    
    free_list(list);
    return 0;
}