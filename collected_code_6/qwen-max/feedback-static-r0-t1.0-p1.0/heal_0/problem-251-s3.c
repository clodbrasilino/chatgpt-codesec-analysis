#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void insert_before_each(Node **head, int insertion_value) {
    if (*head == NULL) return;

    Node *current = *head;
    *head = create_node(insertion_value);
    if (!*head) return;

    Node *inserted = *head;
    while (current) {
        inserted->next = current;
        current = current->next;
        if (current) {
            inserted->next = create_node(insertion_value);
            if (!inserted->next) return;
            inserted = inserted->next;
        }
    }
}

void print_list(Node *head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node *list = NULL;

    list = create_node(1);
    list->next = create_node(2);
    list->next->next = create_node(3);

    printf("Original List: ");
    print_list(list);

    insert_before_each(&list, 0);

    printf("List after insertion: ");
    print_list(list);

    return 0;
}