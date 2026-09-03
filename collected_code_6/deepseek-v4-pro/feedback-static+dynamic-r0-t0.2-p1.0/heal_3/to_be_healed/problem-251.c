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

void insert_before_each(Node **head, int value) {
    if (head == NULL || *head == NULL) {
        return;
    }

    Node *current = *head;
    Node *prev = NULL;

    while (current != NULL) {
        Node *new_node = create_node(value);
        new_node->next = current;

        if (prev == NULL) {
            *head = new_node;
        } else {
            prev->next = new_node;
        }

        prev = current;
        current = current->next;
    }
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
    Node *head = NULL;
    /* Possible weaknesses found:
     *  Assignment 'tail=NULL', assigned value is 0
     */
    Node *tail = NULL;

    int values[] = {1, 2, 3, 4, 5};
    int num_values = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_values; i++) {
        Node *new_node = create_node(values[i]);
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            /* Possible weaknesses found:
             *  Possible null pointer dereference: tail [nullPointer]
             *  Null pointer dereference
             */
            tail->next = new_node;
            tail = new_node;
        }
    }

    printf("Original list: ");
    print_list(head);

    insert_before_each(&head, 0);

    printf("Modified list: ");
    print_list(head);

    free_list(head);

    return 0;
}