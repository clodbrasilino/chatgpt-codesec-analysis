#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void insert_end(Node **head, int value) {
    if (*head == NULL) {
        *head = create_node(value);
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = create_node(value);
    }
}

void remove_negatives(Node **head) {
    Node *current = *head;
    Node *prev = NULL;
    while (current != NULL) {
        if (current->value < 0) {
            if (prev == NULL) {
                *head = current->next;
                free(current);
                current = *head;
            } else {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
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
    Node *head = NULL;
    insert_end(&head, -3);
    insert_end(&head, 4);
    insert_end(&head, -2);
    insert_end(&head, 5);
    insert_end(&head, 6);

    printf("Original list: ");
    print_list(head);

    remove_negatives(&head);

    printf("List after removing negatives: ");
    print_list(head);

    free_list(head);
    return 0;
}